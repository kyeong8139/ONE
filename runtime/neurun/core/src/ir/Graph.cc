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

#include "ir/Graph.h"

#include <algorithm>
#include <bitset>
#include <sstream>

#include "util/logging.h"
#include "verifier/Verifier.h"
#include "ir/operation/LowerInfo.h"
#include "ir/operand/LowerInfo.h"
#include "ir/operand/PermuteFactor.h"
#include "ir/GraphIterator.h"
#include "backend/IConfig.h"

namespace neurun
{
namespace ir
{

Graph::Graph() = default;

Graph::~Graph(void) = default;

OperandIndex Graph::addOperand(const Shape &shape, const TypeInfo &type)
{
  return _operands.emplace(shape, type);
}

OperationIndex Graph::addOperation(std::unique_ptr<Operation> &&node)
{
  assert(isBuildingPhase());
  return _operations.push(std::move(node));
}

void Graph::setOperandValue(const OperandIndex &ind, std::shared_ptr<Data> data)
{
  assert(isBuildingPhase());
  assert(_operands.exist(ind));
  _operands.at(ind).data(std::move(data));
}

void Graph::addInput(const OperandIndex &ind)
{
  assert(isBuildingPhase());
  _inputs.append(ind);
}

void Graph::addOutput(const OperandIndex &ind)
{
  assert(isBuildingPhase());
  _outputs.append(ind);
}

void Graph::finishBuilding(void)
{
  assert(isBuildingPhase());
  _phase = Phase::MODEL;

  // Initialize operand use-def
  initializeUseDef();

  // Call graph verifications for the MODEL phase
  {
    assert(verifier::DAGChecker().verify(*this));
    assert(verifier::EdgeConsistencyChecker().verify(*this));
  }
}

void Graph::initializeUseDef()
{
  operations().iterate([&](const OperationIndex &index, const Operation &node) -> void {
    auto outputs = node.getOutputs();
    for (auto output : outputs)
    {
      operands().at(output).appendDef(index);
    }

    auto inputs = node.getInputs();
    for (auto input : inputs)
    {
      operands().at(input).appendUse(index);
    }
  });
}

} // namespace ir
} // namespace neurun
