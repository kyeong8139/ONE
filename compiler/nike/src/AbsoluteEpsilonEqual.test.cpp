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

#include "nike/AbsoluteEpsilonEqual.h"

#include <cmath> // For "NAN"

#include <gtest/gtest.h>

TEST(AbsoluteEpsilonEqualTest, tolerance)
{
  auto equal = nike::absolute_epsilon_equal(0.001f);

  ASSERT_TRUE(equal(NAN, NAN));
  ASSERT_TRUE(equal(1.0f, 1.0f));
  ASSERT_FALSE(equal(1.0f, 2.0f));
  ASSERT_TRUE(equal(1.0f, 1.0f + 0.0001f));
}
