/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: dijkstra_initializer.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>

namespace sstl {
struct DijkstraInitializer {
  template <typename GraphMatrixType>
  static void Call(GraphMatrixType* graph, const int& start_index,
                   const int& /*end_index*/) {
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      graph->VertexPrior(i) = std::numeric_limits<int>::max();
    }
    graph->VertexPrior(start_index) = 0;
  }
};
}  // namespace sstl
