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

#ifndef __ELTWISE_SQRT_CONVERTER_H__
#define __ELTWISE_SQRT_CONVERTER_H__

#include "CanonicalNodeConverter.h"

#include <loco.h>

namespace exo
{

/**
 * @brief  Convert loco::EltwiseSqrt to TFLSqrt
 */
class EltwiseSqrtConverter : public CanonicalNodeConverter<loco::EltwiseSqrt>
{
public:
  const char *name(void) const final { return "exo::EltwiseSqrtConverter"; }

public:
  bool convert(loco::EltwiseSqrt *origin) final;
};

} // namespace exo

#endif // __ELTWISE_SQRT_CONVERTER_H__
