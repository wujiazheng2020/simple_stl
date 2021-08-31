/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: pfs_treaverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"

namespace sstl {
// priority first search
// it is a algorithm frame
// time complexity: normal at O(n^2)
template <typename PriorInitializer, typename PriorUpdater,
          typename PriorSelector, typename EndConditionFunc>
class PFSTraverser {
 public:
  template <typename GraphMatrixType, typename VisitFunc>
  static void Traverse(GraphMatrixType* graph, const int& start_index,
                       const int& end_index, const VisitFunc& visit_func) {
    graph->ResetState();
    PriorInitializer::Call(graph, start_index, end_index);
    int now_index = start_index;
    visit_func(now_index);
    graph->VertexStatus(now_index) = VISITED;
    while (!EndConditionFunc::Call(graph, now_index, end_index)) {
      // 1.update prior
      for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
        PriorUpdater::Call(graph, now_index, i);
      }

      // 2.get max_prior
      now_index = PriorSelector::Call(graph);
      visit_func(now_index);
      graph->VertexStatus(now_index) = VISITED;
    }
  }
};
}  // namespace sstl
