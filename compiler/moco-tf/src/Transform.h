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

#ifndef __MOCO_TF_TRANSFORM_H__
#define __MOCO_TF_TRANSFORM_H__

#include <loco.h>

#include <logo/Pass.h>

#include <string>

namespace moco
{
namespace tf
{

/**
 * @note  Transform will be replaced by logo::Pass
 */

using Transform = logo::Pass;

std::string transform_name(const Transform *);

template <typename DERIVED> DERIVED *as(loco::Node *node) { return dynamic_cast<DERIVED *>(node); }

} // namespace tf
} // namespace moco

#endif // __MOCO_TF_TRANSFORM_H__
