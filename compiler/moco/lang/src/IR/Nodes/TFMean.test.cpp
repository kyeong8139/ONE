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

#include "moco/IR/Nodes/TFMean.h"
#include "moco/IR/TFDialect.h"

#include <gtest/gtest.h>

TEST(TFMeanTest, constructor)
{
  moco::TFMean mean_node;

  ASSERT_EQ(mean_node.dialect(), moco::TFDialect::get());
  ASSERT_EQ(mean_node.opcode(), moco::TFOpcode::Mean);

  ASSERT_EQ(mean_node.input(), nullptr);
  ASSERT_EQ(mean_node.reduction_indices(), nullptr);
  ASSERT_EQ(mean_node.keep_dims(), false);
}
