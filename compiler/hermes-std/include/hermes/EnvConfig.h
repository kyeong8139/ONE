/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __HERMES_STD_ENV_CONFIG_H__
#define __HERMES_STD_ENV_CONFIG_H__

#include <hermes.h>

#include <string>

namespace hermes
{

using EnvName = std::string;

enum class EnvFormat
{
  // Non-zero -> Enable
  // Zero     -> Diable
  BooleanNumber,
};

template <EnvFormat Format> class EnvConfig;

template <> class EnvConfig<EnvFormat::BooleanNumber> : public Config
{
public:
  EnvConfig(const EnvName &name);

public:
  virtual ~EnvConfig() = default;

public:
  void configure(const Source *, SourceSetting &) const final;

private:
  bool _enabled = false;
};

} // namespace hermes

#endif // __HERMES_STD_ENV_CONFIG_H__
