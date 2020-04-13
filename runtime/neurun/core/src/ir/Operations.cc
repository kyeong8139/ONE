/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "ir/Operations.h"

#include "OperationCloner.h"

namespace neurun
{
namespace ir
{

Operations::Operations(const Operations &obj)
{
  obj.iterate([&](const OperationIndex &index, const Operation &op) {
    OperationCloner cloner;
    op.accept(cloner);
    _objects.emplace(index, cloner.releaseClone());
  });
  _index_count = obj._index_count;
}

} // namespace ir
} // namespace neurun
