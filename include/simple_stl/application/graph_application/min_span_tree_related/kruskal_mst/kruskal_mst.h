/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: krustal_mst.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/sorter/vector_insert_sort.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct TwoEndEdge {
  TwoEndEdge() {}
  TwoEndEdge(const int& the_weight, const int& start_index,
             const int& end_index)
      : weight(the_weight), start(start_index), end(end_index) {}
  ~TwoEndEdge() {}

  bool operator<(const TwoEndEdge& other_edge) {
    return weight > other_edge.weight;
  }

  bool operator==(const TwoEndEdge& other_edge) {
    return weight == other_edge.weight;
  }

  int weight;
  int start;
  int end;
};

// mainly for undirected graph
// result is change parent filed of all node
// after this process you can use the result for union-find set
struct KruskalMST {
  template <typename GraphMatrixType, typename VisitFunc>
  static void Call(GraphMatrixType* graph, bool is_undirected_graph,
                   const VisitFunc& visit_func) {
    graph->ResetState();
    Vector<int> node_type_vec(graph->GetTotalVertexSize(), -1);
    Vector<TwoEndEdge> edges_vec;
    for (int i = 0; i < graph->GetTotalVertexSize(); ++i) {
      for (int j = 0; j < graph->GetTotalVertexSize(); ++j) {
        if (graph->ExistEdge(i, j)) {
          edges_vec.PushBack(TwoEndEdge(graph->EdgeWeight(i, j), i, j));
        }
      }
    }
    sstl::VectorInsertSort::Sort(&edges_vec);

    int max_type = -1;
    Vector<Vector<int>> type_index_vec;
    while (!edges_vec.Empty()) {
      TwoEndEdge now_edge = edges_vec.PopBack();
      if (node_type_vec[now_edge.start] == node_type_vec[now_edge.end]) {
        // 1.1 both -1
        if (node_type_vec[now_edge.start] == -1) {
          ++max_type;
          node_type_vec[now_edge.start] = max_type;
          node_type_vec[now_edge.end] = max_type;
          graph->VertexParent(now_edge.start) = now_edge.end;
          visit_func(now_edge.start);
          visit_func(now_edge.end);
          Vector<int> index_vec;
          index_vec.PushBack(now_edge.start);
          index_vec.PushBack(now_edge.end);
          type_index_vec.PushBack(index_vec);
        }
        // 1.2 if at the same type do nothing
      } else {
        // 2.1 different type, start is -1
        if (node_type_vec[now_edge.start] == -1) {
          node_type_vec[now_edge.start] = node_type_vec[now_edge.end];
          graph->VertexParent(now_edge.start) = now_edge.end;
          type_index_vec[node_type_vec[now_edge.end]].PushBack(now_edge.start);
          visit_func(now_edge.start);
          // 2.2 different type, end is -1 then do nothing
        } else if (node_type_vec[now_edge.start] != -1 &&
                   node_type_vec[now_edge.end] != -1) {
          // 2.3 both no -1 and no equal
          ReverseAllNodeParentToRoot(graph, now_edge.start);
          graph->VertexParent(now_edge.start) = now_edge.end;

          // then change type
          int old_type = node_type_vec[now_edge.start];
          int new_type = node_type_vec[now_edge.end];
          for (int i = 0; i < type_index_vec[old_type].Size(); ++i) {
            node_type_vec[type_index_vec[old_type][i]] = new_type;
            type_index_vec[new_type].PushBack(type_index_vec[old_type][i]);
          }
          type_index_vec[old_type].Clear();
          // for undirected node
          if (is_undirected_graph) {
            edges_vec.PopBack();
          }
          // todo(wujiazheng): judge merge left or right acording to the
          // node_height
        }
      }
    }
  }

 private:
  template <typename GraphMatrixType>
  static void ReverseAllNodeParentToRoot(GraphMatrixType* graph,
                                         const int& start_index) {
    int last_index = start_index;
    int now_index = graph->VertexParent(last_index);
    while (now_index != -1) {
      int next_index = graph->VertexParent(now_index);
      graph->VertexParent(now_index) = last_index;

      last_index = now_index;
      now_index = next_index;
    }
  }
};
}  // namespace sstl
