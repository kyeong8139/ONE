/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "luci/IR/Nodes/CircleRelu6.h"

#include "luci/IR/CircleDialect.h"

#include <gtest/gtest.h>

TEST(CircleRelu6Test, constructor_P)
{
  luci::CircleRelu6 relu6_node;

  ASSERT_EQ(relu6_node.dialect(), luci::CircleDialect::get());
  ASSERT_EQ(relu6_node.opcode(), luci::CircleOpcode::RELU6);

  ASSERT_EQ(relu6_node.features(), nullptr);
}
