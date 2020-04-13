/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __NEURUN_GRAPH_PASS_CONSTANT_INSERTION_PASS_H__
#define __NEURUN_GRAPH_PASS_CONSTANT_INSERTION_PASS_H__

#include <ir/operand/PermuteFactor.h>
#include <ir/Index.h>
#include "LoweredOperationPass.h"
#include <unordered_map>
#include <utility>

namespace neurun
{
namespace ir
{
namespace pass
{

class ConstantInsertionPass : public LoweredOperationPass
{
public:
  using LoweredOperationPass::LoweredOperationPass;

public:
  std::string id() final { return "ConstantInsertionPass"; }

public:
  void callback(const OperationIndex &index, Operation &node) final;

private:
  struct ReplaceKey
  {
    OperandIndex index;
    operand::PermuteFactor factor;

    bool operator==(const ReplaceKey &other) const
    {
      return index == other.index && factor == other.factor;
    }
  };

  /**
   * @brief Structure that provides hash function of ReplaceKey
   */
  struct KeyHasher
  {
    std::size_t operator()(const ReplaceKey &key) const noexcept
    {
      using std::hash;
      return hash<OperandIndex>()(key.index) ^ (hash<operand::PermuteFactor>()(key.factor) << 1);
    }
  };

  std::unordered_map<ReplaceKey, OperandIndex, KeyHasher> _replace_operands_map;
};

} // namespace pass
} // namespace ir
} // namespace neurun

#endif // __NEURUN_GRAPH_PASS_CONSTANT_INSERTION_PASS_H__
