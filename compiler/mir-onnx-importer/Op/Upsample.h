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

#ifndef MIR_ONNX_OP_UPSAMPLE_H
#define MIR_ONNX_OP_UPSAMPLE_H

#include "ONNXNodeConverterRegistry.h"

namespace mir_onnx
{

void convertUpsampleV1(const onnx::NodeProto &onnx_node, ConverterContext *context);
void convertUpsampleV7(const onnx::NodeProto &onnx_node, ConverterContext *context);
void convertUpsampleV9(const onnx::NodeProto &onnx_node, ConverterContext *context);

} // namespace mir_onnx

#endif // MIR_ONNX_OP_UPSAMPLE_H
