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

#include <iostream>

#include "simple_stl/container/graph/graph_matrix.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct ZeroInTopoSorter {
  // return index vector
  // if it can't topo sort the outsize is less than the total vertex size
  template <typename GraphMatrixType>
  static Vector<int> Sort(GraphMatrixType* graph) {
    Vector<int> indegree_vec(graph->GetTotalVertexSize());
    Vector<int> topo_vec;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      indegree_vec[i] = graph->VertexInDegree(i);
    }

    while (topo_vec.Size() < graph->GetTotalVertexSize()) {
      bool has_zero_in = false;
      for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
        if (indegree_vec[i] == 0) {
          has_zero_in = true;
          topo_vec.PushBack(i);
          indegree_vec[i] = -1;
          for (int j = 0; j < graph->GetTotalVertexSize(); ++j) {
            if (i != j && graph->ExistEdge(i, j)) {
              --indegree_vec[j];
            }
          }
          break;
        }
      }
      if (!has_zero_in) {
        std::cout << "can't topo sort" << std::endl;
        return topo_vec;
      }
    }
    return topo_vec;
  }
};
}  // namespace sstl
