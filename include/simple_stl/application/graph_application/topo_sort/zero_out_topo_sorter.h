/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: zero_out_topo_sorter.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/reverser/vector_reverser.h"
#include "simple_stl/container/graph/graph_matrix.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct ZeroOutTopoSorter {
  // return index vector
  // if it can't topo sort the outsize is less than the total vertex size
  template <typename GraphMatrixType>
  static Vector<int> Sort(GraphMatrixType* graph) {
    Vector<int> topo_vec;
    if (!Traverse(graph, &topo_vec)) {
      std::cout << "can't topo sort" << std::endl;
    }
    VectorReverser::Reverse(&topo_vec);
    return topo_vec;
  }

 private:
  template <typename GraphMatrixType>
  static bool Traverse(GraphMatrixType* graph, Vector<int>* index_vec,
                       const int& start_index, int* clock) {
    ++(*clock);
    graph->VertexStatus(start_index) = DISCOVERED;
    graph->VertexFirstTime(start_index) = *clock;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (i != start_index && graph->ExistEdge(start_index, i)) {
        if (graph->VertexStatus(i) == UNDISCOVERED) {
          graph->EdgeStatus(start_index, i) = TREE;
          graph->VertexParent(i) = start_index;
          if (!Traverse(graph, index_vec, i, clock)) {
            return false;
          }
        } else if (graph->VertexStatus(i) == DISCOVERED) {
          graph->EdgeStatus(start_index, i) = BACKWARD;
          return false;
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
    index_vec->PushBack(start_index);
    ++(*clock);
    graph->VertexLastTime(start_index) = *clock;
    return true;
  }

  // for each connected field
  template <typename GraphMatrixType>
  static bool Traverse(GraphMatrixType* graph, Vector<int>* index_vec) {
    graph->ResetState();
    int clock = 0;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      if (graph->VertexStatus(i) == UNDISCOVERED) {
        if (!Traverse(graph, index_vec, i, &clock)) {
          return false;
        }
      }
    }
    return true;
  }
};
}  // namespace sstl
