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

/*
 * Copyright (c) 2017 ARM Limited.
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

#include "helpers.h"

#if defined(DATA_TYPE) && defined(AXIS) && defined(INDICES_DIM)

/** Performs the Gather operation along the chosen axis
 * @note Datatype should be given as a preprocessor argument using -DDATA_TYPE=type. e.g.
 *       -DDATA_TYPE=short
 * @note Axis should be given as a preprocessor argument using -DAXIS=axis. e.g. -DAXIS=1
 * @attention Output tensor depth should be given as a preprocessor argument using
 *            -DOUTPUT_DIM_Z=size. e.g. -DOUTPUT_DIM_Z=16
 * @attention Input tensor depth should be given as a preprocessor argument using
 *            -DINPUT_DIM_Z=size. e.g. -DINPUT_DIM_Z=16
 *
 * @param[in]  input_ptr                             Pointer to the source tensor. Supported data
 *                                                   types: U8/S8/U16/S16/U32/S32/F16/F32
 * @param[in]  input_stride_x                        Stride of the source tensor in X dimension (in
 *                                                   bytes)
 * @param[in]  input_step_x                          input_stride_x * number of elements along X
 *                                                   processed per work item (in bytes)
 * @param[in]  input_stride_y                        Stride of the source tensor in Y dimension (in
 *                                                   bytes)
 * @param[in]  input_step_y                          input_stride_y * number of elements along Y
 *                                                   processed per work item (in bytes)
 * @param[in]  input_stride_z                        Stride of the source tensor in Y dimension (in
 *                                                   bytes)
 * @param[in]  input_step_z                          input_stride_z * number of elements along Z
 *                                                   processed per work item (in bytes)
 * @param[in]  input_stride_w                        Stride of the source tensor in Z dimension (in
 *                                                   bytes)
 * @param[in]  input_step_w                          input_stride_w * number of elements along W
 *                                                   processed per work item (in bytes)
 * @param[in]  input_offset_first_element_in_bytes   Offset of the first element in the source
 *                                                   tensor
 * @param[in]  indices_ptr                           Pointer to the source tensor. Supported data
 *                                                   types: S32
 * @param[in]  indices_stride_x                      Stride of the source tensor in X dimension (in
 *                                                   bytes)
 * @param[in]  indices_step_x                        indices_stride_x * number of elements along X
 *                                                   processed per workitem(in  bytes)
 * @param[in]  indices_stride_y                      Stride of the source tensor in Y dimension (in
 *                                                   bytes)
 * @param[in]  indices_step_y                        indices_stride_y * number of elements along Y
 *                                                   processed per workitem(in  bytes)
 * @param[in]  indices_stride_z                      Stride of the source tensor in Z dimension (in
 *                                                   bytes)
 * @param[in]  indices_step_z                        indices_stride_z * number of elements along Z
 *                                                   processed per workitem(in  bytes)
 * @param[in]  indices_offset_first_element_in_bytes The offset of the first element in the
 *                                                   destination tensor
 * @param[out] output_ptr                            Pointer to the destination tensor. Supported
 *                                                   data types: same as @p input_ptr
 * @param[in]  output_stride_x                       Stride of the destination tensor in X dimension
 *                                                   (in bytes)
 * @param[in]  output_step_x                         output_stride_x * number of elements along X
 *                                                   processed per work item (in bytes)
 * @param[in]  output_stride_y                       Stride of the destination tensor in Y dimension
 *                                                   (in bytes)
 * @param[in]  output_step_y                         output_stride_y * number of elements along Y
 *                                                   processed per work item (in bytes)
 * @param[in]  output_stride_z                       Stride of the destination tensor in Z dimension
 *                                                   (in bytes)
 * @param[in]  output_step_z                         output_stride_z * number of elements along Z
 *                                                   processed per work item (in bytes)
 * @param[in]  output_stride_w                       Stride of the destination tensor in W dimension
 *                                                   (in bytes)
 * @param[in]  output_step_w                         output_stride_w * number of elements along W
 *                                                   processed per work item (in bytes)
 * @param[in]  output_offset_first_element_in_bytes  Offset of the first element in the destination
 *                                                   tensor
 */
__kernel void gather_ex(TENSOR4D_DECLARATION(input), TENSOR3D_DECLARATION(indices),
                        TENSOR4D_DECLARATION(output))
{
  const int px = get_global_id(0);
  const int py = get_global_id(1);
  const int pz = get_global_id(2) % OUTPUT_DIM_Z;
  const int pw = get_global_id(2) / OUTPUT_DIM_Z;

  const Tensor4D input = CONVERT_TO_TENSOR4D_STRUCT_NO_STEP(input, INPUT_DIM_Z);
  const Tensor3D indices = CONVERT_TO_TENSOR3D_STRUCT_NO_STEP(indices);
  Tensor4D output = CONVERT_TO_TENSOR4D_STRUCT(output, OUTPUT_DIM_Z);

#if AXIS == 0
#if INDICES_DIM == 1
  const uint index = *(__global const uint *)tensor3D_offset(&indices, px, 0, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, index, py, pz, pw);
#elif INDICES_DIM == 2
  const uint index = *(__global const uint *)tensor3D_offset(&indices, px, py, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, index, pz, pw, 0);
#elif INDICES_DIM == 3
  const uint index = *(__global const uint *)tensor3D_offset(&indices, px, py, pz);
  __global const uchar *input_addr = tensor4D_offset(&input, index, pw, 0, 0);
#endif
#elif AXIS == 1
#if INDICES_DIM == 1
  const uint index = *(__global const uint *)tensor3D_offset(&indices, py, 0, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, px, index, pz, pw);
#elif INDICES_DIM == 2
  const uint index = *(__global const uint *)tensor3D_offset(&indices, py, pz, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, px, index, pw, 0);
#elif INDICES_DIM == 3
  const uint index = *(__global const uint *)tensor3D_offset(&indices, py, pz, pw);
  __global const uchar *input_addr = tensor4D_offset(&input, px, index, 0, 0);
#endif
#elif AXIS == 2
#if INDICES_DIM == 1
  const uint index = *(__global const uint *)tensor3D_offset(&indices, pz, 0, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, px, py, index, pw);
#elif INDICES_DIM == 2
  const uint index = *(__global const uint *)tensor3D_offset(&indices, pz, pw, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, px, py, index, 0);
#endif
#elif AXIS == 3
#if INDICES_DIM == 1
  const uint index = *(__global const uint *)tensor3D_offset(&indices, pw, 0, 0);
  __global const uchar *input_addr = tensor4D_offset(&input, px, py, pz, index);
#endif
#endif // AXIS

  *(__global DATA_TYPE *)output.ptr = *((__global const DATA_TYPE *)input_addr);
}

#endif // defined(DATA_TYPE) && defined(AXIS) && defined(INDICES_DIM)
