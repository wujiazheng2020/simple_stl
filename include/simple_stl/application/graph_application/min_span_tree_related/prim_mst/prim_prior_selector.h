/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: prim_prior_selector.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>
#include "simple_stl/container/graph/graph_matrix.h"

namespace sstl {
// select max
struct PrimPriorSelector {
  template <typename GraphMatrixType>
  static int Call(GraphMatrixType* graph) {
    int shortest_cost = std::numeric_limits<int>::max();
    int shortest_index = 0;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) != VISITED &&
          graph->VertexPrior(i) < shortest_cost) {
        shortest_cost = graph->VertexPrior(i);
        shortest_index = i;
      }
    }
    return shortest_index;
  }
};
}  // namespace sstl
