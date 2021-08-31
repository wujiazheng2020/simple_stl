/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: bfs_treaverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"
#include "simple_stl/container/queue/queue.h"

namespace sstl {
// if you just want one start BFS
// please graph->ResetState() first
struct BfsTraverser {
  template <typename GraphMatrixType, typename VisitFunc>
  static void Traverse(GraphMatrixType* graph, const int& start_index,
                       int* clock, VisitFunc visit_fun) {
    Queue<int> index_queue;
    graph->VertexStatus(start_index) = DISCOVERED;
    index_queue.Enqueue(start_index);
    while (!index_queue.Empty()) {
      int now_index = index_queue.Dequeue();
      ++(*clock);
      graph->VertexFirstTime(now_index) = *clock;
      for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
        if (i != now_index && graph->ExistEdge(now_index, i)) {
          if (graph->VertexStatus(i) == UNDISCOVERED) {
            graph->VertexStatus(i) = DISCOVERED;
            index_queue.Enqueue(i);
            graph->EdgeStatus(now_index, i) = TREE;
            graph->VertexParent(i) = now_index;
          } else {
            graph->EdgeStatus(now_index, i) = CROSS;
          }
        }
      }
      graph->VertexStatus(now_index) = VISITED;
      visit_fun(now_index);
    }
  }

  // for each connected field
  template <typename GraphMatrixType, typename VisitFunc>
  static void Traverse(GraphMatrixType* graph, VisitFunc visit_fun) {
    graph->ResetState();
    int clock = 0;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) == UNDISCOVERED) {
        Traverse(graph, i, &clock, visit_fun);
      }
    }
  }
};
}  // namespace sstl
