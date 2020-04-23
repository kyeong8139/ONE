/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

// This file has no ifdef guard intentionally

#include "ir/operation/BatchToSpaceND.h"
#include "ir/operation/Conv2D.h"
#include "ir/operation/MaxPool2D.h"
#include "ir/operation/AvgPool2D.h"
#include "ir/operation/Concat.h"
#include "ir/operation/Reshape.h"
#include "ir/operation/FullyConnected.h"
#include "ir/operation/Softmax.h"
#include "ir/operation/Transpose.h"
#include "ir/operation/Permute.h"
#include "ir/operation/ReduceSum.h"
#include "ir/operation/Add.h"
#include "ir/operation/Sub.h"
#include "ir/operation/DepthwiseConv2D.h"
#include "ir/operation/Slice.h"
#include "ir/operation/StridedSlice.h"
#include "ir/operation/Mul.h"
#include "ir/operation/Squeeze.h"
#include "ir/operation/Tanh.h"
#include "ir/operation/Logistic.h"
#include "ir/operation/Cast.h"
#include "ir/operation/Div.h"
#include "ir/operation/Exp.h"
#include "ir/operation/ReduceMax.h"
#include "ir/operation/Comparison.h"
#include "ir/operation/LogicalAnd.h"
#include "ir/operation/LogicalOr.h"
#include "ir/operation/LogicalNot.h"
#include "ir/operation/LSTM.h"
#include "ir/operation/RSQRT.h"
#include "ir/operation/ReLU.h"
#include "ir/operation/ResizeBilinear.h"
#include "ir/operation/ReLU1.h"
#include "ir/operation/ReLU6.h"
#include "ir/operation/RNN.h"
#include "ir/operation/Floor.h"
#include "ir/operation/SpaceToBatchND.h"
#include "ir/operation/SpaceToDepth.h"
#include "ir/operation/L2Pool2D.h"
#include "ir/operation/EmbeddingLookup.h"
#include "ir/operation/L2Normalization.h"
#include "ir/operation/HashtableLookup.h"
#include "ir/operation/InstanceNorm.h"
#include "ir/operation/PReLU.h"
#include "ir/operation/TransposeConv.h"
#include "ir/operation/SQRT.h"
#include "ir/operation/SquaredDifference.h"
#include "ir/operation/TopKV2.h"
#include "ir/operation/Gather.h"
#include "ir/operation/Neg.h"
#include "ir/operation/Abs.h"
#include "ir/operation/ArgMax.h"
#include "ir/operation/Dequantize.h"
#include "ir/operation/Mean.h"
#include "ir/operation/LocalResponseNormalization.h"
#include "ir/operation/DepthToSpace.h"
#include "ir/operation/Pack.h"
#include "ir/operation/ReduceMin.h"
#include "ir/operation/Split.h"
#include "ir/operation/Unpack.h"
#include "ir/operation/Pad.h"
#include "ir/operation/Min.h"
#include "ir/operation/Max.h"
#include "ir/operation/Custom.h"
#include "ir/operation/OneHot.h"
#include "ir/operation/Sin.h"
#include "ir/operation/Shape.h"
#include "ir/operation/ConvertFp32ToFp16.h"
#include "ir/operation/ConvertFp16ToFp32.h"
#include "ir/operation/ReduceProd.h"
#include "ir/operation/While.h"
