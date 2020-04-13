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

#include "coco/IR/Input.h"
#include "coco/IR/BagManager.h"

#include <nncc/core/ADT/tensor/IndexEnumerator.h>

#include <gtest/gtest.h>

using nncc::core::ADT::tensor::Shape;
using nncc::core::ADT::tensor::IndexEnumerator;

TEST(IR_INPUT, ctor_should_set_shape)
{
  const nncc::core::ADT::tensor::Shape shape{1, 3, 3, 1};
  coco::Input input{shape};

  ASSERT_EQ(input.shape(), shape);
  ASSERT_TRUE(input.name().empty());
}

TEST(IR_INPUT, bag_update)
{
  // Create a bag
  coco::BagManager bag_mgr;

  auto bag = bag_mgr.create(9);

  const nncc::core::ADT::tensor::Shape shape{1, 3, 3, 1};
  coco::Input input{shape};

  input.bag(bag);
  ASSERT_EQ(input.bag(), bag);

  // bag(...) method SHOULD update 'bag' type
  ASSERT_TRUE(bag->isInput());
}

TEST(IR_INPUT, name_update)
{
  const nncc::core::ADT::tensor::Shape shape{1, 3, 3, 1};
  coco::Input input{shape};

  input.name("data");
  ASSERT_EQ(input.name(), "data");
}

TEST(IR_INPUT, at)
{
  const Shape shape{1, 3, 3, 1};
  coco::Input input{shape};

  coco::Input *mutable_ptr = &input;
  const coco::Input *immutable_ptr = &input;

  for (IndexEnumerator e{shape}; e.valid(); e.advance())
  {
    mutable_ptr->at(e.current()) = coco::ElemID{16};
  }

  for (IndexEnumerator e{shape}; e.valid(); e.advance())
  {
    ASSERT_EQ(immutable_ptr->at(e.current()).value(), 16);
  }
}
