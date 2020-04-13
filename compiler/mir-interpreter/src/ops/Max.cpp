/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Max.h"
#include "Common.h"

#include "mir/ShapeRange.h"
#include "mir/Tensor.h"

#include <algorithm>

namespace mir_interpreter
{

using namespace mir;

template <typename T> struct MaxImpl
{
  static void run(const TensorVariant &lhs, const TensorVariant &rhs, TensorVariant &res);
};

template <typename T>
void MaxImpl<T>::run(const TensorVariant &lhs, const TensorVariant &rhs, TensorVariant &res)
{
  TensorVariant broadcasted_lhs(lhs, res.getShape());
  TensorVariant broadcasted_rhs(rhs, res.getShape());
  Tensor<T> lhs_accessor(broadcasted_lhs);
  Tensor<T> rhs_accessor(broadcasted_rhs);
  Tensor<T> res_accessor(res);

  for (const auto &index : ShapeRange(res.getShape()))
  {
    res_accessor.at(index) = std::max(lhs_accessor.at(index), rhs_accessor.at(index));
  }
}
template <> struct MaxImpl<uint8_t>
{
  static void run(const TensorVariant &lhs, const TensorVariant &rhs, TensorVariant &res)
  {
    throw std::runtime_error{"NYI"};
  };
};

void Max(const TensorVariant &lhs, const TensorVariant &rhs, TensorVariant &res)
{
  if (lhs.getElementType() != rhs.getElementType())
  {
    throw std::runtime_error{"Max with different input types is unsupported"};
  }
  dispatch<MaxImpl>(lhs.getElementType(), lhs, rhs, res);
}

} // namespace mir_interpreter
