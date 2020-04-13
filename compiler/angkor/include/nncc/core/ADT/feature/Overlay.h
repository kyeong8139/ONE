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

#ifndef __NNCC_CORE_ADT_FEATURE_OVERLAY_H__
#define __NNCC_CORE_ADT_FEATURE_OVERLAY_H__

#include "nncc/core/ADT/feature/View.h"

#include <vector>

namespace nncc
{
namespace core
{
namespace ADT
{
namespace feature
{

template <typename T> class Overlay final : public View<T>
{
public:
  explicit Overlay(const Shape &shape, const Layout &layout, T *base)
      : View<T>{shape, layout}, _base{base}
  {
    // DO NOTHING
  }

public:
  virtual T *base(void) { return _base; }
  virtual const T *base(void) const { return _base; }

private:
  T *const _base;
};

template <typename T, typename LayoutImpl> Overlay<T> make_overlay(const Shape &shape, T *base)
{
  return Overlay<T>{shape, LayoutImpl{}, base};
}

} // namespace feature
} // namespace ADT
} // namespace core
} // namespace nncc

#endif // __NNCC_CORE_ADT_FEATURE_OVERLAY_H__
