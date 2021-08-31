/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: zero_in_topo_sorter.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph_matrix.h"
#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct BiconnectedDecomposite {
  // time complexity O(n + e)
  // we use the concept hca(v) = highest connected ancestor of v
  // 1. when DFS find backward edge(v, u), then
  //      hca(v) = min(hca(v), dTime(u))
  // 2. when DFS(u) finish and back to its parent v, then
  //      if hca(u) < dTime(v), it show v can't be key node, then
  //         hca(v) = min (hca(v), hca(u))
  //      else: v is the key node
  template <typename GraphMatrixType>
  static Vector<Vector<int>*> Decomposite(GraphMatrixType* graph) {
    return Traverse(graph);
  }

 private:
  template <typename GraphMatrixType>
  static void Traverse(GraphMatrixType* graph, const int& start_index,
                       int* clock, Stack<int>* index_stack,
                       Vector<Vector<int>*>* bcc_vector) {
    ++(*clock);
    graph->VertexStatus(start_index) = DISCOVERED;
    graph->VertexFirstTime(start_index) = *clock;
    graph->VertexLastTime(start_index) = *clock;
    index_stack->Push(start_index);
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (i != start_index && graph->ExistEdge(start_index, i)) {
        if (graph->VertexStatus(i) == UNDISCOVERED) {
          graph->VertexParent(i) = start_index;
          Traverse(graph, i, clock, index_stack, bcc_vector);
          // we use VertexLastTime for hca;
          if (graph->VertexLastTime(i) < graph->VertexFirstTime(start_index)) {
            graph->VertexLastTime(start_index) = std::min(
                graph->VertexLastTime(start_index), graph->VertexLastTime(i));
          } else {
            Vector<int>* tmp_index_vec = new Vector<int>();
            while (index_stack->Top() != start_index) {
              tmp_index_vec->PushBack(index_stack->Pop());
            }
            tmp_index_vec->PushBack(index_stack->Top());
            bcc_vector->PushBack(tmp_index_vec);
          }
        } else if (graph->VertexStatus(i) == DISCOVERED) {
          if (i != graph->VertexParent(start_index)) {
            graph->VertexLastTime(start_index) = std::min(
                graph->VertexLastTime(start_index), graph->VertexFirstTime(i));
          }
        }
      }
    }
    graph->VertexStatus(start_index) = VISITED;
  }

  // for each connected field
  template <typename GraphMatrixType>
  static Vector<Vector<int>*> Traverse(GraphMatrixType* graph) {
    graph->ResetState();
    int clock = 0;
    Stack<int> index_stack;
    Vector<Vector<int>*> bcc_vector;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) == UNDISCOVERED) {
        Traverse(graph, i, &clock, &index_stack, &bcc_vector);
      }
    }
    return bcc_vector;
  }
};

}  // namespace sstl
