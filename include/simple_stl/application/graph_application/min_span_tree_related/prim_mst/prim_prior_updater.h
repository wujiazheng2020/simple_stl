/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: prim_prior_updater.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"

namespace sstl {
struct PrimPriorUpdater {
  template <typename GraphMatrixType>
  static void Call(GraphMatrixType* graph, const int& now_index,
                   const int& target_index) {
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) != VISITED && now_index != i &&
          graph->ExistEdge(now_index, i)) {
        if (graph->VertexPrior(i) > graph->EdgeWeight(now_index, i)) {
          graph->VertexPrior(i) = graph->EdgeWeight(now_index, i);
          // for output the tree
          graph->VertexParent(i) = now_index;
        }
      }
    }
  }
};
}  // namespace sstl
