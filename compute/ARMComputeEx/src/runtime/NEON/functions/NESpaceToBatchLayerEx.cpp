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

/*
 * Copyright (c) 2019 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "arm_compute/runtime/NEON/functions/NESpaceToBatchLayerEx.h"

#include "arm_compute/core/Error.h"
#include "arm_compute/core/TensorInfo.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/core/Validate.h"
#include "arm_compute/runtime/NEON/NEScheduler.h"

namespace arm_compute
{
NESpaceToBatchLayerEx::NESpaceToBatchLayerEx()
    : _space_to_batch_kernel(), _memset_kernel(), _has_padding(false)
{
}

void NESpaceToBatchLayerEx::configure(const ITensor *input, const ITensor *block_shape,
                                      const ITensor *paddings, ITensor *output)
{
  ARM_COMPUTE_ERROR_ON_NULLPTR(input, block_shape, paddings, output);

  if (input->info()->tensor_shape().total_size() != output->info()->tensor_shape().total_size())
  {
    _has_padding = true;
    _memset_kernel.configure(
        output, PixelValue(0, output->info()->data_type(), output->info()->quantization_info()));
  }
  _space_to_batch_kernel.configure(input, block_shape, paddings, output);
}

void NESpaceToBatchLayerEx::configure(const ITensor *input, const int block_shape_x,
                                      const int block_shape_y, const Size2D &padding_left,
                                      const Size2D &padding_right, ITensor *output)
{
  ARM_COMPUTE_ERROR_ON_NULLPTR(input, output);

  if (input->info()->tensor_shape().total_size() != output->info()->tensor_shape().total_size())
  {
    _has_padding = true;
    _memset_kernel.configure(
        output, PixelValue(0, output->info()->data_type(), output->info()->quantization_info()));
  }
  _space_to_batch_kernel.configure(input, block_shape_x, block_shape_y, padding_left, padding_right,
                                   output);
}

Status NESpaceToBatchLayerEx::validate(const ITensorInfo *input, const ITensorInfo *block_shape,
                                       const ITensorInfo *paddings, const ITensorInfo *output)
{
  ARM_COMPUTE_RETURN_ON_ERROR(
      NESpaceToBatchLayerKernel::validate(input, block_shape, paddings, output));

  return Status{};
}

Status NESpaceToBatchLayerEx::validate(const ITensorInfo *input, const int block_shape_x,
                                       const int block_shape_y, const Size2D &padding_left,
                                       const Size2D &padding_right, const ITensorInfo *output)
{
  ARM_COMPUTE_RETURN_ON_ERROR(NESpaceToBatchLayerKernel::validate(
      input, block_shape_x, block_shape_y, padding_left, padding_right, output));

  return Status{};
}

void NESpaceToBatchLayerEx::run()
{
  // Zero out output only if we have paddings
  if (_has_padding)
  {
    NEScheduler::get().schedule(&_memset_kernel, Window::DimY);
  }
  NEScheduler::get().schedule(&_space_to_batch_kernel, Window::DimY);
}
} // namespace arm_compute
