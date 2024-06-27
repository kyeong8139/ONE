/*
 * Copyright (c) 2024 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "import/helpers/OMSpacesBatchesNDCommon.h"

using namespace onert_micro;
using namespace onert_micro::core;

namespace
{

constexpr uint32_t input1TensorIdx = 0;
constexpr uint32_t input2TensorIdx = 1;
constexpr uint32_t input3TensorIdx = 2;
constexpr uint32_t outputTensorIdx = 0;

} // namespace

OMStatus onert_micro::import::helpers::configure_spaces_batches_nd_kernel_common(
  const OMConfigureArgs &config_args)
{
  OMRuntimeContext &runtime_context = config_args.runtime_context;
  uint16_t op_index = config_args.kernel_index;

  onert_micro::execute::OMRuntimeKernel runtime_kernel;

  OMStatus status = runtime_kernel.readKernel(op_index, runtime_context);
  if (status != Ok)
    return status;

  const circle::Tensor *input1 = runtime_kernel.inputs[input1TensorIdx];
  const circle::Tensor *input2 = runtime_kernel.inputs[input2TensorIdx];
  const circle::Tensor *input3 = runtime_kernel.inputs[input3TensorIdx];
  const circle::Tensor *output = runtime_kernel.outputs[outputTensorIdx];

  core::OMRuntimeShape input1_shape(input1);
  core::OMRuntimeShape output_shape(output);

  assert(input1 != nullptr);
  assert(input2 != nullptr);
  assert(input3 != nullptr);
  assert(output != nullptr);

  status = utils::checkCondition(input1->type() == output->type());
  if (status != Ok)
    return status;

  status = utils::checkCondition(input2->type() == circle::TensorType_INT32);
  if (status != Ok)
    return status;

  status = utils::checkCondition(input3->type() == circle::TensorType_INT32);
  if (status != Ok)
    return status;

  status = utils::checkCondition(output_shape.dimensionsCount() >= 3);
  if (status != Ok)
    return status;

  status = utils::checkCondition(input1_shape.dimensionsCount() >= 3);
  if (status != Ok)
    return status;

  status = utils::checkCondition(output_shape.dimensionsCount() <= 4);
  if (status != Ok)
    return status;

  status = utils::checkCondition(input1_shape.dimensionsCount() <= 4);
  if (status != Ok)
    return status;

  return status;
}
