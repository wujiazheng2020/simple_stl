/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: dfs_treaverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"
#include "simple_stl/container/queue/queue.h"

namespace sstl {
// if you just want one start DFS
// please graph->ResetState() first
struct DFSTraverser {
  template <typename GraphMatrixType, typename VisitFunc>
  static void Traverse(GraphMatrixType* graph, const int& start_index,
                       int* clock, VisitFunc visit_fun) {
    ++(*clock);
    graph->VertexStatus(start_index) = DISCOVERED;
    visit_fun(start_index);
    graph->VertexFirstTime(start_index) = *clock;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (i != start_index && graph->ExistEdge(start_index, i)) {
        if (graph->VertexStatus(i) == UNDISCOVERED) {
          graph->EdgeStatus(start_index, i) = TREE;
          graph->VertexParent(i) = start_index;
          Traverse(graph, i, clock, visit_fun);
        } else if (graph->VertexStatus(i) == DISCOVERED) {
          graph->EdgeStatus(start_index, i) = BACKWARD;
        } else {
          if (graph->VertexFirstTime(start_index) < graph->VertexFirstTime(i)) {
            graph->EdgeStatus(start_index, i) = FORWARD;
          } else {
            graph->EdgeStatus(start_index, i) = CROSS;
          }
        }
      }
    }
    graph->VertexStatus(start_index) = VISITED;
    ++(*clock);
    graph->VertexLastTime(start_index) = *clock;
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
