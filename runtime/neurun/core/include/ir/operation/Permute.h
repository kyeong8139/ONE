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

#ifndef __NEURUN_IR_OPERATION_PERMUTE_H__
#define __NEURUN_IR_OPERATION_PERMUTE_H__

#include "ir/Operation.h"

namespace neurun
{
namespace backend
{
class BackendContext;
} // namespace backend
} // namespace neurun

namespace neurun
{
namespace ir
{
namespace operation
{

class Permute : public Operation
{
public:
  enum class Type
  {
    NHWC_TO_NCHW,
    NCHW_TO_NHWC,
    COPY
  };

  struct Param
  {
    const backend::BackendContext *input_backend_ctx;
    const backend::BackendContext *output_backend_ctx;
  };

public:
  void accept(OperationVisitor &v) const override;
  OpCode opcode() const final { return OpCode::Permute; }

public:
  Permute(const OperandIndex &input, const OperandIndex &output,
          const backend::BackendContext *input_backend_ctx,
          const backend::BackendContext *output_backend_ctx, Type type,
          DataType data_type = DataType::FLOAT32);

public:
  const Param &param() const { return _param; }
  DataType getDataType() const { return _dataType; }
  Type getPermuteType() const { return _type; }

private:
  Param _param;
  Type _type;
  DataType _dataType;
};

} // namespace operation
} // namespace ir
} // namespace neurun

#endif // __NEURUN_IR_OPERATION_PERMUTE_H__
