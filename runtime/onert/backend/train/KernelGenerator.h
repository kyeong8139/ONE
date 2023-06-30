/*
 * Copyright (c) 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_BACKEND_TRAIN_KERNEL_GENERATOR_H__
#define __ONERT_BACKEND_TRAIN_KERNEL_GENERATOR_H__

#include "ExternalContext.h"
#include "backend/basic/TensorRegistry.h"
#include "TensorBuilder.h"
#include "Tensor.h"

// Remove including this header
#include <backend/basic/KernelGeneratorBase.h>
#include <backend/train/KernelGeneratorBase.h>
#include <ir/Operands.h>
#include <ir/Operations.h>

namespace onert
{
namespace backend
{
namespace train
{

// TODO Remove this class
class InferenceKernelGenerator : public basic::KernelGeneratorBase
{
public:
  InferenceKernelGenerator(const ir::Graph &graph,
                           const std::shared_ptr<TensorBuilder> &tensor_builder,
                           const std::shared_ptr<basic::TensorRegistry> &tensor_reg,
                           const std::shared_ptr<custom::IKernelBuilder> &kernel_builder,
                           const std::shared_ptr<ExternalContext> &external_context);

  std::unique_ptr<exec::FunctionSequence> generate(ir::OperationIndex op_ind) override;

  void visit(const ir::operation::Conv2D &) override;
  void visit(const ir::operation::Pool2D &) override;

private:
  const ir::Operands &_ctx;
  const ir::Operations &_operations_ctx;
  ir::Layout _current_layout;
  std::shared_ptr<TensorBuilder> _tensor_builder;
  std::shared_ptr<basic::TensorRegistry> _tensor_reg;
  std::shared_ptr<backend::custom::IKernelBuilder> _kernel_builder;
  const std::shared_ptr<ExternalContext> _external_context;
};

class KernelGenerator : public backend::train::KernelGeneratorBase
{
public:
  KernelGenerator(const ir::train::TrainableGraph &tgraph,
                  const std::shared_ptr<basic::TensorRegistry> &tensor_reg,
                  const std::shared_ptr<basic::TensorRegistry> &grad_tensor_reg,
                  const std::shared_ptr<ExternalContext> &external_context);

  std::unique_ptr<exec::train::TrainableFnSequence> generate(ir::OperationIndex op_ind) override;

  void visit(const ir::train::operation::Loss &) override;

private:
  ir::Layout _current_layout;
  std::shared_ptr<basic::TensorRegistry> _tensor_reg;
  std::shared_ptr<basic::TensorRegistry> _grad_tensor_reg;
  const std::shared_ptr<ExternalContext> _external_context;
};

} // namespace train
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_TRAIN_KERNEL_GENERATOR_H__
