/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __EXO_TFL_EXPORTER_H__
#define __EXO_TFL_EXPORTER_H__

#include <loco.h>

#include <memory>

namespace exo
{

/**
 * HOW TO USE:
 *
 *   loco::Graph *g = ...;
 *
 *   TFLExporter e(g);
 *   e.dumpToFile("model.tflite");
 *
 * HOW TO USE (simplified):
 *
 *   TFLExporter(g).dumpToFile("model.tflite");
 *
 */
class TFLExporter
{
public:
  class Impl;

public:
  explicit TFLExporter(loco::Graph *graph);
  ~TFLExporter();

  /**
   * @brief write to a file
   * @param path path to file where to write data
   * @throws any file related exceptions
   */
  void dumpToFile(const char *path) const;

private:
  std::unique_ptr<Impl> _impl;
};

} // namespace exo

#endif // __EXO_TFL_EXPORTER_H__
