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

#ifndef __OP_ACTIVATION_H__
#define __OP_ACTIVATION_H__

#include <coco/IR/Block.h>
#include <coco/IR/FeatureObject.h>

#include <schema_generated.h>

namespace tflimport
{

/**
 * @brief Add coco::Eval for fused activation.
 *        This method creates an ofm object, appends Eval(ofm object, RELU(...)) into block,
 *        and returns ofm object.
 */
coco::FeatureObject *build_activation(tflite::ActivationFunctionType act, coco::Block *block,
                                      coco::FeatureObject *ifm);
} // namespace tflimport

#endif // __OP_ACTIVATION_H__
