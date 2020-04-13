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

#ifndef __NEURUN_IR_OPERATION_ADD_H__
#define __NEURUN_IR_OPERATION_ADD_H__

#include "ir/Operation.h"
#include "ir/InternalType.h"

namespace neurun
{
namespace ir
{
namespace operation
{

class Add : public Operation
{
public:
  enum Input
  {
    LHS = 0,
    RHS
  };

  struct Param
  {
    Activation activation;
  };

public:
  Add(const OperandIndexSequence &inputs, const OperandIndexSequence &outputs, const Param &param);

public:
  void accept(OperationVisitor &v) const override;
  OpCode opcode() const final { return OpCode::Add; }

public:
  const Param &param() const { return _param; }

private:
  Param _param;
};

} // namespace operation
} // namespace ir
} // namespace neurun

#endif // __NEURUN_IR_OPERATION_ADD_H__
