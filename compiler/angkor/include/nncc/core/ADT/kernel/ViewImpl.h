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

#ifndef __NNCC_CORE_ADT_KERNEL_VIEW_IMPL_H__
#define __NNCC_CORE_ADT_KERNEL_VIEW_IMPL_H__

#include "nncc/core/ADT/kernel/Shape.h"
#include "nncc/core/ADT/kernel/Layout.h"

namespace nncc
{
namespace core
{
namespace ADT
{
namespace kernel
{

template <typename T> class ViewImpl
{
public:
  explicit ViewImpl(const Shape &shape, const Layout &layout) : _shape{shape}, _layout{layout}
  {
    // DO NOTHING
  }

public:
  template <typename InputIt>
  T at(InputIt it, uint32_t nth, uint32_t ch, uint32_t row, uint32_t col) const
  {
    return *(it + _layout.offset(_shape, nth, ch, row, col));
  }

public:
  template <typename InputIt>
  T &at(InputIt it, uint32_t nth, uint32_t ch, uint32_t row, uint32_t col)
  {
    return *(it + _layout.offset(_shape, nth, ch, row, col));
  }

public:
  const Shape &shape(void) const { return _shape; }

private:
  const Shape _shape;
  const Layout _layout;
};

} // namespace kernel
} // namespace ADT
} // namespace core
} // namespace nncc

#endif // __NNCC_CORE_ADT_KERNEL_VIEW_IMPL_H__
