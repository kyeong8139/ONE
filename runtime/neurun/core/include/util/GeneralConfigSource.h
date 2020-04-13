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

#ifndef __NEURUN_UTIL_GLOBAL_CONFIG_SOURCE_H__
#define __NEURUN_UTIL_GLOBAL_CONFIG_SOURCE_H__

#include <unordered_map>

#include "util/IConfigSource.h"

namespace neurun
{
namespace util
{

class GeneralConfigSource : public IConfigSource
{
public:
  GeneralConfigSource() = default;

  std::string get(const std::string &key) const override;
  void set(const std::string &key, const std::string &val);

private:
  std::unordered_map<std::string, std::string> _map;
};

} // namespace util
} // namespace neurun

#endif // __NEURUN_UTIL_GLOBAL_CONFIG_SOURCE_H__
