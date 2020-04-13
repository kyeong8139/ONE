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

#include "loco/IR/Node.h"

#include "MockupNode.h"

#include <gtest/gtest.h>

TEST(NodeTest, preds)
{
  ::MockupNode arg;
  ::MockupNode node;

  node.in(&arg);

  auto preds = loco::preds(&node);

  ASSERT_EQ(preds.size(), 1);
  ASSERT_NE(preds.find(&arg), preds.end());
}

TEST(NodeTest, succs)
{
  ::MockupNode node;
  ::MockupNode succ_1;
  ::MockupNode succ_2;

  succ_1.in(&node);
  succ_2.in(&node);

  auto succs = loco::succs(&node);

  ASSERT_EQ(succs.size(), 2);
  ASSERT_NE(succs.find(&succ_1), succs.end());
  ASSERT_NE(succs.find(&succ_2), succs.end());
}

TEST(NodeTest, replace_with)
{
  ::MockupNode node_1;
  ::MockupNode node_2;

  ::MockupNode node_3;
  ::MockupNode node_4;

  node_3.in(&node_1);
  node_4.in(&node_2);

  // The following holds at this point
  // - node_3 USE node_1
  // - node_4 USE node_2
  ASSERT_EQ(node_3.in(), &node_1);
  ASSERT_EQ(node_4.in(), &node_2);

  // Replace all the usage of node_1 with node_2
  replace(&node_1).with(&node_2);

  // The following holds at this point
  // - node_3 USE node_2
  // - node_4 USE node_2
  ASSERT_EQ(node_3.in(), &node_2);
  ASSERT_EQ(node_4.in(), &node_2);
}

TEST(NodeTest, constructor)
{
  MockupNode node;

  // graph() SHOULD return nullptr if node is not constructed through "Graph"
  ASSERT_EQ(node.graph(), nullptr);
}

// TODO Rewrite this as a FixedAritry mix-in test
#if 0
TEST(FixedArityNodeTest, constructor)
{
  struct DerivedNode final : public loco::FixedArityNode<1, loco::Node>
  {
    loco::Dialect *dialect(void) const final { return MockDialect::get(); }
    uint32_t opnum(void) const final { return 0; }
  };

  DerivedNode node;

  ASSERT_EQ(node.arity(), 1);
  ASSERT_EQ(node.arg(0), nullptr);
}
#endif
