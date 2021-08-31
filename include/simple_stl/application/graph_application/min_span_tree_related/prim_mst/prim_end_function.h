/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: prim_end_function.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"

namespace sstl {
struct PrimEndFunction {
  template <typename GraphMatrixType>
  static bool Call(GraphMatrixType* graph, const int& /*now_index*/,
                   const int& /*end_index*/) {
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) != VISITED) {
        return false;
      }
    }
    return true;
  }
};
}  // namespace sstl
