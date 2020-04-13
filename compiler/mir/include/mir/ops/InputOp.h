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

#ifndef _MIR_OPS_INPUT_OP_H_
#define _MIR_OPS_INPUT_OP_H_

#include "mir/Operation.h"

namespace mir
{
namespace ops
{

class InputOp : public Operation
{
public:
  // @brief Deprecated [use TensorType for creation of Input]
  explicit InputOp(const Shape &shape) : Operation(Type::input, {})
  {
    setOutputType(0, {mir::DataType::UNKNOWN, shape});
  }

  explicit InputOp(const TensorType &type) : Operation(Type::input, {}) { setOutputType(0, type); }

  Operation *copyWithInputs(const std::vector<Output *> &input) override
  {
    assert(false && "copying graph input is not allowed");
    (void)input;
    return nullptr;
  }
};

} // namespace ops
} // namespace mir

#endif //_MIR_OPS_INPUT_OP_H_
