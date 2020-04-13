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

#include "nest/expr/DerefNode.h"

#include <memory>

#include <gtest/gtest.h>

namespace
{
struct DummyNode final : public nest::expr::Node
{
};
}

TEST(DEREF_NODE, cast)
{
  const nest::DomainID dom_id{0};

  auto derived = std::make_shared<nest::expr::DerefNode>(dom_id, std::make_shared<DummyNode>());
  std::shared_ptr<nest::expr::Node> base = derived;

  ASSERT_NE(derived.get(), nullptr);
  ASSERT_EQ(base->asDeref(), derived.get());
}
