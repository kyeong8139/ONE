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

#ifndef __LOCOEX_SERVICE_COP_SHAPE_INFERENCE_RULE_H__
#define __LOCOEX_SERVICE_COP_SHAPE_INFERENCE_RULE_H__

#include <loco/Service/ShapeInferenceRule.h>
#include <loco/IR/Dialect.h>
#include <loco/IR/Node.h>
#include <loco/IR/NodeShape.h>

namespace locoex
{

/**
 * @brief Shape inference rule for COpDialect
 *
 * @note the shape of inputs and output of CopCall must belong to loco::Domain::Tensor
 */
struct COpShapeInferenceRule final : public loco::ShapeInferenceRule
{
  bool recognize(const loco::Dialect *) const final;
  bool infer(const loco::Node *, loco::NodeShape &) const final;
};

} // namespace locoex

#endif // __LOCOEX_SERVICE_COP_SHAPE_INFERENCE_RULE_H__
