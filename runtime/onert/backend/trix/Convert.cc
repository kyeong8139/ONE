/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Convert.h"

namespace onert
{
namespace backend
{
namespace trix
{

data_layout convertDataLayout(const ir::Layout layout)
{
  switch (layout)
  {
    case ir::Layout::NCHW:
      return DATA_LAYOUT_NCHW;
    case ir::Layout::NHWC:
      return DATA_LAYOUT_NHWC;
    default:
      throw std::runtime_error("Unknown Layout");
  }
}

data_type convertDataType(const ir::DataType type)
{
  switch (type)
  {
    case ir::DataType::QUANT_UINT8_ASYMM:
      return DATA_TYPE_QASYMM8;
    case ir::DataType::QUANT_INT16_SYMM:
      return DATA_TYPE_QSYMM16;
    default:
      throw std::runtime_error("Unsupported data type");
  }
}

} // namespace trix
} // namespace backend
} // namespace onert
