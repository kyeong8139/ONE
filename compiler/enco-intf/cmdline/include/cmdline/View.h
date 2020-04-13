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

#ifndef __CMDLINE_VIEW_H__
#define __CMDLINE_VIEW_H__

#include <cstdint>

namespace cmdline
{

struct View
{
  virtual ~View() = default;

  virtual uint32_t size(void) const = 0;
  virtual const char *at(uint32_t n) const = 0;
};

} // namespace cmdline

#endif // __CMDLINE_VIEW_H__
