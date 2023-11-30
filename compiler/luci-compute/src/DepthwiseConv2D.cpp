/* Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "luci_compute/Types.h"
#include "luci_compute/DepthwiseConv2D.h"

#include "ConvertTypes.h"

#include <tensorflow/lite/kernels/internal/reference/depthwiseconv_float.h>

#include <cassert>
#include <cstdint>

namespace luci
{
namespace compute
{

bool DepthwiseConv2D::prepare(void)
{
  // TODO support other ranks if necessary
  if (_input_shape.rank() != 4 || _filter_shape.rank() != 4)
    return false;
  // if bias exist, check if rank is 1
  if (_bias_data && _bias_shape.rank() != 1)
    return false;

  auto const input_batches = _input_shape.dim(0).value();
  auto const input_height = _input_shape.dim(1).value();
  auto const input_width = _input_shape.dim(2).value();
  auto const input_depth = _input_shape.dim(3).value();

  auto const filter_height = _filter_shape.dim(1).value();
  auto const filter_width = _filter_shape.dim(2).value();
  auto const filter_channels_out = _filter_shape.dim(3).value();

  if (filter_channels_out % input_depth != 0)
    return false; // wrong input/output depth ratio

  if (_params.depth_multiplier != static_cast<int32_t>(filter_channels_out / input_depth))
    return false; // wrong depth multiplier value

  if (_bias_shape.dim(0).value() != filter_channels_out)
    return false; // unsupported bias value

  // TODO compute output
  auto output_height = 0;
  auto output_width = 0;

  _output_shape.rank(4);
  _output_shape.dim(0) = input_batches;
  _output_shape.dim(1) = output_height;
  _output_shape.dim(2) = output_width;
  _output_shape.dim(3) = filter_channels_out;

  // TODO compute padding
  _params.padding_values.height = 0;
  _params.padding_values.width = 0;

  return true;
}

void DepthwiseConv2D::compute(void)
{
  assert(_input_data != nullptr);
  assert(_filter_data != nullptr);
  // NOTE _bias_shape can be nullptr
  assert(_output_data != nullptr);

  // NOTE if this fails, structure may have changed
  static_assert(sizeof(compute::DepthwiseParams) == sizeof(tflite::DepthwiseParams));

  tflite::DepthwiseParams params;

  // clang-format off
  params.padding_type                   = tflite::PaddingType::kSame; // TODO convert type
  params.padding_values.width           = _params.padding_values.width;
  params.padding_values.height          = _params.padding_values.height;
  params.padding_values.width_offset    = _params.padding_values.width_offset;
  params.padding_values.height_offset   = _params.padding_values.height_offset;
  params.stride_width                   = _params.stride_width;
  params.stride_height                  = _params.stride_height;
  params.dilation_width_factor          = _params.dilation_width_factor;
  params.dilation_height_factor         = _params.dilation_height_factor;
  params.depth_multiplier               = _params.depth_multiplier;
  params.input_offset                   = _params.input_offset;
  params.weights_offset                 = _params.weights_offset;
  params.output_offset                  = _params.output_offset;
  params.output_multiplier              = _params.output_multiplier;
  params.output_shift                   = _params.output_shift;
  params.quantized_activation_min       = _params.quantized_activation_min;
  params.quantized_activation_max       = _params.quantized_activation_max;
  params.float_activation_min           = _params.float_activation_min;
  params.float_activation_max           = _params.float_activation_max;
  params.output_multiplier_per_channel  = _params.output_multiplier_per_channel;
  params.output_shift_per_channel       = _params.output_shift_per_channel;
  // clang-format on

  tflite::reference_ops::DepthwiseConv(
    params, tflite_shape(_input_shape), _input_data, tflite_shape(_filter_shape), _filter_data,
    tflite_shape(_bias_shape), _bias_data, tflite_shape(_output_shape), _output_data);
}

} // namespace compute
} // namespace luci
