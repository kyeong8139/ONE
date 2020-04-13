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

#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#include <loco.h>

#include <tensorflow/core/framework/graph.pb.h>

#define STRING_CONTENT(content) #content

namespace moco
{
namespace tf
{
namespace test
{

template <typename T> T *find_first_node_bytype(loco::Graph *g)
{
  T *first_node = nullptr;
  loco::Graph::NodeContext *nodes = g->nodes();
  uint32_t count = nodes->size();

  for (uint32_t i = 0; i < count; ++i)
  {
    first_node = dynamic_cast<T *>(nodes->at(i));
    if (first_node != nullptr)
      break;
  }

  return first_node;
}

template <typename T> std::vector<T *> find_nodes_bytype(loco::Graph *g)
{
  std::vector<T *> find_nodes;
  loco::Graph::NodeContext *nodes = g->nodes();
  uint32_t count = nodes->size();

  for (uint32_t i = 0; i < count; ++i)
  {
    auto node = dynamic_cast<T *>(nodes->at(i));
    if (node != nullptr)
      find_nodes.push_back(node);
  }

  return find_nodes;
}

/**
 * @brief Append setup output of graph by adding loco::Push node
 *
 * @note  This is subject to change when loco changes I/O treatment
 */
void setup_output_node(loco::Graph *graph, loco::Node *last_node);

} // namespace test
} // namespace tf
} // namespace moco

#include <moco/IR/TFNode.h>

#include <moco/Import/GraphBuilder.h>

#include <plier/tf/TestHelper.h>

namespace moco
{
namespace tf
{
namespace test
{

class TFNodeBuildTester
{
public:
  TFNodeBuildTester();

public:
  void inputs(const std::vector<std::string> &names);
  void output(const char *name);
  moco::TFNode *output(void);

  void run(tensorflow::NodeDef &node_def, moco::GraphBuilder &graph_builder);

private:
  std::unique_ptr<moco::SymbolTable> _tensor_names;
  std::unique_ptr<loco::Graph> _graph;

  std::vector<moco::TFNode *> _inputs;
  const char *_output{nullptr};
};

} // namespace test
} // namespace tf
} // namespace moco

#endif // __TEST_HELPER_H__
