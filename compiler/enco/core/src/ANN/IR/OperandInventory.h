/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ANN_IR_OPERAND_INVENTORY_H__
#define __ANN_IR_OPERAND_INVENTORY_H__

#include "ANN/IR/OperandID.h"
#include "ANN/IR/Operand.h"

#include <nncc/core/ADT/tensor/Shape.h>

#include <memory>
#include <vector>

namespace ann
{

class OperandInventory
{
public:
  OperandID create(const DType &);
  OperandID create(const DType &, const nncc::core::ADT::tensor::Shape &);

public:
  template <typename Callable> void each(Callable &&cb) const
  {
    for (uint32_t n = 0; n < _operands.size(); ++n)
    {
      cb(OperandID{n}, _operands.at(n).get());
    }
  }

public:
  Operand *at(const OperandID &id);
  const Operand *at(const OperandID &id) const;

private:
  std::vector<std::unique_ptr<Operand>> _operands;
};

} // namespace ann

#endif // __ANN_IR_OPERAND_INVENTORY_H__
