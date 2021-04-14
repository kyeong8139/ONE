/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
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
 * Copyright (c) 2019-2020 ARM Limited.
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
#ifndef ARM_COMPUTE_CLPADLAYERKERNELEX_H
#define ARM_COMPUTE_CLPADLAYERKERNELEX_H

#include "src/core/CL/ICLKernel.h"
#include "arm_compute/core/CL/ICLTensor.h"

namespace arm_compute
{
class ICLTensor;

/** Interface for the PadLayer function. */
class CLPadLayerKernelEx : public ICLKernel
{
public:
  /** Default constructor */
  CLPadLayerKernelEx();
  /** Prevent instances of this class from being copied (As this class contains pointers) */
  CLPadLayerKernelEx(const CLPadLayerKernelEx &) = delete;
  /** Prevent instances of this class from being copied (As this class contains pointers) */
  CLPadLayerKernelEx &operator=(const CLPadLayerKernelEx &) = delete;
  /** Allow instances of this class to be moved */
  CLPadLayerKernelEx(CLPadLayerKernelEx &&) = default;
  /** Allow instances of this class to be moved */
  CLPadLayerKernelEx &operator=(CLPadLayerKernelEx &&) = default;
  /** Default destructor */
  ~CLPadLayerKernelEx() = default;
  /** Set the input and output tensor.
   *
   * @param[in]  input          Source tensor. Data types supported: U8, S8, QASYMM8,
   * QASYMM8_SIGNED, U16, S16, U32, S32, F16, F32.
   * @param[out] output         Output tensor. Data type supported: same as @p input
   * @param[in]  padding        The padding for each spatial dimension of the input tensor. The pair
   * padding[i] specifies the front and the end padding in the i-th dimension.
   * @param[in]  constant_value (Optional) Constant value to be used for the padding.
   * @param[in]  mode           (Optional) Controls whether the padding should be filled with @p
   * constant_value using CONSTANT, or reflect the input, either including the border values
   * (SYMMETRIC) or not (REFLECT).
   */
  void configure(const ICLTensor *input, ICLTensor *output, const PaddingList &padding,
                 PixelValue constant_value = PixelValue(),
                 PaddingMode mode = PaddingMode::CONSTANT);
  /** Set the input and output tensor.
   *
   * @param[in]  compile_context The compile context to be used.
   * @param[in]  input           Source tensor. Data types supported: All.
   * @param[out] output          Output tensor. Data type supported: same as @p input
   * @param[in]  padding         The padding for each spatial dimension of the input tensor. The
   * pair padding[i] specifies the front and the end padding in the i-th dimension.
   * @param[in]  constant_value  (Optional) Constant value to be used for the padding.
   * @param[in]  mode            (Optional) Controls whether the padding should be filled with @p
   * constant_value using CONSTANT, or reflect the input, either including the border values
   * (SYMMETRIC) or not (REFLECT).
   */
  void configure(const CLCompileContext &compile_context, const ICLTensor *input, ICLTensor *output,
                 const PaddingList &padding, PixelValue constant_value = PixelValue(),
                 PaddingMode mode = PaddingMode::CONSTANT);
  /** Static function to check if given info will lead to a valid configuration of @ref
   * CLPadLayerKernelEx
   *
   * @param[in] input          Source tensor info. Data types supported: U8, S8, QASYMM8,
   * QASYMM8_SIGNED, U16, S16, U32, S32, F16, F32.
   * @param[in] output         Output tensor info. Data type supported: same as @p input
   * @param[in] padding        The padding for each spatial dimension of the input tensor. The pair
   * padding[i] specifies the front and the end padding in the i-th dimension.
   * @param[in] constant_value (Optional) Constant value to be used for the padding.
   * @param[in] mode           (Optional) Controls whether the padding should be filled with @p
   * constant_value using CONSTANT, or reflect the input, either including the border values
   * (SYMMETRIC) or not (REFLECT).
   */
  static Status validate(const ITensorInfo *input, const ITensorInfo *output,
                         const PaddingList &padding, PixelValue constant_value = PixelValue(),
                         PaddingMode mode = PaddingMode::CONSTANT);

  // Inherited methods overridden:
  void run(const Window &window, cl::CommandQueue &queue) override;

private:
  const ICLTensor *_input;
  ICLTensor *_output;
  int _input_start_x;
  int _input_start_y;
  bool _4d_enabled;
};
} // namespace arm_compute
#endif /*ARM_COMPUTE_CLPADLAYERKERNELEX_H */
