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

/**
 * @file    ResizeBilinear.h
 * @ingroup COM_AI_RUNTIME
 * @brief   This file defines internal::tflite::op::ResizeBilinear::Param struct
 *          and internal::tflite::op::ResizeBilinear::Node class
 */
#ifndef __INTERNAL_OP_RESIZE_BILINEAR_H__
#define __INTERNAL_OP_RESIZE_BILINEAR_H__

#include "internal/op/Node.h"

#include <cstdint>

namespace internal
{
namespace tflite
{
namespace op
{
namespace ResizeBilinear
{

/**
 * @brief Struct to have indexes for ResizeBilinear operation parameter
 */
struct Param
{
  int32_t ofm_index; /**< Index of output feature map */

  int32_t ifm_index;    /**< Index of input feature map */
  int32_t height_index; /**< Index of height */
  int32_t width_index;  /**< Index of width */
  /**
   * @brief Construct as default
   */
  Param() = default;
  /**
   * @brief Construct a new Param object with params
   * @param[in] inputCount  Count of inputs
   * @param[in] inputs      Pointer of inputs
   * @param[in] outputCount Count of outputs
   * @param[in] outputs     Pointer of outputs
   */
  Param(uint32_t inputCount, const uint32_t *inputs, uint32_t outputCount, const uint32_t *outputs);
};

/**
 * @brief Class to represent an ResizeBilinear operation of data structure
 */
class Node final : public op::Node
{
public:
  /**
   * @brief Construct a new Node object with param
   * @param[in] param Param object that makes up a Node
   */
  Node(const Param &param) : _param(param)
  {
    // DO NOTHING
  }

public:
  /**
   * @brief Destruct as default
   */
  virtual ~Node() = default;

public:
  /**
   * @brief  Get a reference of Param object
   * @return Reference of Param object
   */
  const Param &param(void) const { return _param; }

public:
  /**
   * @brief Visit this Node by NodeVisitor
   * @param[in] v Visitor
   * @return N/A
   */
  void accept(NodeVisitor &&) const override;

private:
  const Param _param;
};

} // namespace ResizeBilinear
} // namespace op
} // namespace tflite
} // namespace internal

#endif // __INTERNAL_OP_RESIZE_BILINEAR_H__
