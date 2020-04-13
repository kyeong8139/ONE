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

#ifndef __NEURUN_BACKEND_ACL_CL_BACKEND_H__
#define __NEURUN_BACKEND_ACL_CL_BACKEND_H__

#include <memory>
#include <backend/Backend.h>

#include "Config.h"
#include "ConstantInitializer.h"
#include "KernelGenerator.h"
#include "ShapeFixer.h"
#include "TensorManager.h"
#include "Optimizer.h"

namespace neurun
{
namespace backend
{
namespace acl_cl
{

class Backend : public ::neurun::backend::Backend
{
public:
  Backend() : _config{std::make_shared<Config>()} {}

  std::shared_ptr<IConfig> config() const override { return _config; }

  std::unique_ptr<BackendContext> newContext(const ir::Graph &graph,
                                             const std::shared_ptr<custom::IKernelBuilder> &,
                                             bool is_linear_executor) const override
  {
    const auto &operands = graph.operands();
    auto context = std::make_unique<BackendContext>(this, &graph);
    auto tb = std::make_shared<TensorBuilder>(operands, createTensorManager(is_linear_executor));
    context->tensor_builder = tb;
    context->constant_initializer = std::make_shared<ConstantInitializer>(operands, tb);
    context->kernel_gen = std::make_shared<KernelGenerator>(operands, tb);
    context->shape_fixer = std::make_shared<ShapeFixer>(operands, tb);
    context->tensor_register = nullptr;
    context->optimizer = nullptr;
    return context;
  }

private:
  std::shared_ptr<IConfig> _config;
};

} // namespace acl_cl
} // namespace backend
} // namespace neurun

#endif // __NEURUN_BACKEND_ACL_CL_BACKEND_H__
