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

#ifndef __MOCO_IR_TFNODE_VISITOR_FORWARD_H__
#define __MOCO_IR_TFNODE_VISITOR_FORWARD_H__

namespace moco
{

// NOTE These forward declarations SHOULD BE aligned with Node delcarations in
// "TFNodeVisitor.h"
template <typename T> struct TFNodeVisitorBase;
template <typename T> struct TFNodeMutableVisitorBase;

} // namespace moco

#endif // __MOCO_IR_TFNODE_VISITOR_FORWARD_H__
