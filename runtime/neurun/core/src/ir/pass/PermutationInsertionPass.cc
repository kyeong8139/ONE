/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PermutationInsertionPass.h"

#include <cassert>
#include <utility>
#include <unordered_map>

#include "ir/Operand.h"
#include "ir/operation/LowerInfo.h"
#include "ir/Graph.h"
#include "backend/IConfig.h"
#include "util/logging.h"
#include "memory"
#include "ir/operation/Permute.h"

namespace neurun
{
namespace ir
{
namespace pass
{

void PermutationInsertionPass::callback(const OperandIndex &index, Operand &object)
{
  auto &&operand_li = _lowered_graph.getLowerInfo(index);
  assert(operand_li);

  // NOTE Later, constants also will have Def
  // Ignore constants
  if (operand_li->def_factors().size() == 0)
  {
    return;
  }

  std::list<OperationIndex> permute_indexes;

  // Build a map for all necessary type of operands
  std::unordered_map<operand::PermuteFactor, OperandIndex> factor_to_index;
  {
    assert(operand_li->def_factors().size() == 1);
    for (auto factor : operand_li->def_factors())
    {
      factor_to_index.emplace(factor, index);
    }

    auto insert_set = operand_li->use_factors() - operand_li->def_factors();
    for (auto factor : insert_set)
    {
      const auto permute_operation_index = insertPermute(index, factor);
      permute_indexes.push_back(permute_operation_index);
      VERBOSE(PermutationInsertionPass) << "Insert 'Permute' operation for operand "
                                        << index.value() << std::endl;
      const auto &permute_operation = _graph.operations().at(permute_operation_index);
      const auto permuted_operand_index = permute_operation.getOutputs().at(0);
      factor_to_index.emplace(factor, permuted_operand_index);
    }
  }

  // Update operations' input that uses this operand
  {
    std::list<OperationIndex> remove_list;

    auto uses = object.getUses();
    for (auto use : uses.list())
    {
      // If permute operation, ignore it
      if (std::find(permute_indexes.begin(), permute_indexes.end(), use) != permute_indexes.end())
        continue;

      auto &operation = _graph.operations().at(use);
      assert(_lowered_graph.op_seqs().containsOperation(use));
      auto op_seq_index = _lowered_graph.op_seqs().getOperation(use);
      auto op_seq_li = _lowered_graph.getLowerInfo(op_seq_index);
      assert(op_seq_li);
      const auto op_seq_layout = op_seq_li->layout();
      const backend::Backend *backend = op_seq_li->backend();
      assert(backend);
      auto use_node_inputs = operation.getInputs();
      assert(use_node_inputs.contains(index));

      auto new_index = factor_to_index.at({backend, op_seq_layout});
      if (index != new_index)
      {
        // Update from op_seq
        _lowered_graph.op_seqs().at(op_seq_index).replaceInput(index, new_index);

        // Update from operation
        operation.replaceInput(index, new_index);

        // Update from operand
        remove_list.push_back(
            use); // Removal should be done in another loop since we are in the loop
        _graph.operands().at(new_index).appendUse(use);
      }
    }

    for (auto &operation : remove_list)
    {
      object.removeUse(operation);
    }
  }
}

OperationIndex PermutationInsertionPass::insertPermute(const OperandIndex &operand_index,
                                                       const operand::PermuteFactor &factor)
{
  assert(!_graph.isBuildingPhase());

  auto &operand = _graph.operands().at(operand_index);

  // Generate output operand and permute operation
  auto out_operand_index = _graph.addOperand(operand.shape(), operand.typeInfo());
  // change model output if operand_index is model output index
  auto &model_outputs = _graph.getOutputs();
  if (model_outputs.contains(operand_index))
  {
    model_outputs.replace(operand_index, out_operand_index);
  }

  // Find Permute information
  auto input_backend =
      _lowered_graph.getLowerInfo(operand_index)->def_factors().getOnlyElement().backend();
  auto output_backend = factor.backend();
  // NOTE Permute may not have specific layout because the layout of input and output may be
  // different.
  const auto permute_node_layout = Layout::UNKNOWN;
  const auto permute_node_backend = compiler::BackendManager::get().getDefault();
  const operand::PermuteFactor permute_node_factor{permute_node_backend, permute_node_layout};

  // Update LowerInfo of input operand
  auto operand_lower_info = _lowered_graph.getLowerInfo(operand_index);
  operand_lower_info->removeUsePermuteFactor(factor);
  operand_lower_info->addUsePermuteFactor(permute_node_factor);

  // Update LowerInfo of output operand
  auto out_operand_li = std::make_unique<operand::LowerInfo>();

  // The input and output factors of all nodes will be the same except Permute. So Tensor's
  // allocators allocates memory using only the information of def permutation factor now.
  // TODO Change param to permute_node_factor
  out_operand_li->addDefPermuteFactor(factor);
  out_operand_li->addUsePermuteFactor(factor);
  _lowered_graph.setLowerInfo(out_operand_index, std::move(out_operand_li));

  auto input_backend_ctx = _lowered_graph.backend_contexts().at(input_backend).get();
  auto output_backend_ctx = _lowered_graph.backend_contexts().at(output_backend).get();

  // Insert permute operation to the graph
  const auto input_layout =
      _lowered_graph.getLowerInfo(operand_index)->def_factors().getOnlyElement().layout();
  const auto output_layout = factor.layout();
  using Permute = operation::Permute;
  const auto permute_type = [&]() {
    if (input_layout == Layout::NHWC && output_layout == Layout::NCHW)
    {
      return Permute::Type::NHWC_TO_NCHW;
    }
    else if (input_layout == Layout::NCHW && output_layout == Layout::NHWC)
    {
      return Permute::Type::NCHW_TO_NHWC;
    }
    else
    {
      return Permute::Type::COPY;
    }
  }();
  auto insert_node = std::make_unique<Permute>(operand_index, out_operand_index, input_backend_ctx,
                                               output_backend_ctx, permute_type);

  auto node_index = _graph.operations().push(std::move(insert_node));
  const auto &node = _graph.operations().at(node_index);

  // OpSequence
  {
    auto op_seq_index = _lowered_graph.op_seqs().emplace(node_index, node, permute_node_layout);
    auto &subg = _lowered_graph.op_seqs().at(op_seq_index);
    subg.setInputs(node.getInputs());
    subg.setOutputs(node.getOutputs());
    _lowered_graph.setLowerInfo(op_seq_index, std::make_unique<operation::LowerInfo>(
                                                  permute_node_backend, permute_node_layout));
  }

  // Update Use/Def info
  {
    _graph.operands().at(operand_index).appendUse(node_index);
    _graph.operands().at(out_operand_index).appendDef(node_index);
  }
  return node_index;
}
} // namespace pass
} // namespace ir
} // namespace neurun
