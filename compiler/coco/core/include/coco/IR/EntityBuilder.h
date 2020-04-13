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

#ifndef __COCO_IR_ENTITY_BUILDER_H__
#define __COCO_IR_ENTITY_BUILDER_H__

#include "coco/IR/Entity.h"
#include "coco/IR/Module.forward.h"

namespace coco
{

/**
 * @brief A base class for IR entity builders
 *
 * NOTE Only EntityBuilder is allowed to update module field of each Entity
 */
class EntityBuilder
{
public:
  virtual ~EntityBuilder() = default;

protected:
  Module *module(void) const { return _module; }

  void module(Module *m) { _module = m; }
  void modulize(Entity *entity) const { entity->module(_module); }

private:
  Module *_module = nullptr;
};

} // namespace coco

#endif // __COCO_IR_ENTITY_BUILDER_H__
