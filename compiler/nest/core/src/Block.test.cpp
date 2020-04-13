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

#include "nest/Block.h"

#include <gtest/gtest.h>

namespace
{
struct DummyNode final : public nest::stmt::Node
{
  // Dummy Node for testing
};
}

TEST(BLOCK, use_case_1)
{
  nest::Block block;

  ASSERT_EQ(block.size(), 0);

  auto stmt = std::make_shared<DummyNode>();

  block.append(stmt);

  ASSERT_EQ(block.size(), 1);
  ASSERT_EQ(block.at(0), stmt);
}
