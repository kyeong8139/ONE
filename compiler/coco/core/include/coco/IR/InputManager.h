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

#ifndef __COCO_IR_INPUT_MANAGER_H__
#define __COCO_IR_INPUT_MANAGER_H__

#include "coco/IR/Input.h"
#include "coco/IR/EntityBuilder.h"

#include "coco/ADT/PtrManager.h"

namespace coco
{

class InputManager final : public PtrManager<Input>, public EntityBuilder
{
public:
  InputManager(Module *m = nullptr) { module(m); }

public:
  Input *create(const nncc::core::ADT::tensor::Shape &);
};

} // namespace coco

#endif // __COCO_IR_INPUT_MANAGER_H__
