/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: dijkstra_end_function.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// find shortest path from all (i,j) pair (i,j)belongs to [0, vertex_size)
// i is not equal to j
// time complexity: O(n^3)
// but it is better than dijkstra for each (i,j) pair
struct FloydIterative {
  template <typename GraphMatrixType>
  static Vector<Vector<int>> Call(const GraphMatrixType& graph) {
    Vector<int> rows(graph.GetTotalVertexSize(),
                     std::numeric_limits<int>::max());
    Vector<Vector<int>> shortest_path(graph.GetTotalVertexSize(), rows);
    // 1.init
    for (int i = 0; i < graph.GetTotalVertexSize(); ++i) {
      for (int j = 0; j < graph.GetTotalVertexSize(); ++j) {
        if (graph.ExistEdge(i, j)) {
          shortest_path[i][j] = graph.EdgeWeight(i, j);
        }
      }
    }

    // 2.iterative
    for (int k = 0; k < graph.GetTotalVertexSize(); ++k) {
      for (int i = 0; i < graph.GetTotalVertexSize(); ++i) {
        for (int j = 0; j < graph.GetTotalVertexSize(); ++j) {
          if (shortest_path[i][k] != std::numeric_limits<int>::max() &&
              shortest_path[k][j] != std::numeric_limits<int>::max()) {
            shortest_path[i][j] = std::min(
                shortest_path[i][j], shortest_path[i][k] + shortest_path[k][j]);
          }
        }
      }
    }
    return shortest_path;
  }
};
}  // namespace sstl
