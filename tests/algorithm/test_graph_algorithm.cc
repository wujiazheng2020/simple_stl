/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_list_algorithm.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/graph_algorithm/traverser/bfs_traverser.h"
#include "simple_stl/algorithm/graph_algorithm/traverser/dfs_traverser.h"
#include "simple_stl/container/graph/graph_matrix.h"

TEST(TEST_GTAPH_ALGORITHM, TEST_BFS) {
  sstl::GraphMatrix<int, int> my_graph;
  my_graph.InsertVertex(5);
  my_graph.InsertVertex(6);
  my_graph.InsertVertex(7);
  my_graph.InsertVertex(8);
  my_graph.InsertVertex(9);
  my_graph.InsertVertex(7);
  my_graph.InsertVertex(9);
  my_graph.InsertVertex(10);
  my_graph.InsertVertex(11);
  my_graph.InsertVertex(65);
  my_graph.InsertVertex(65);
  my_graph.InsertVertex(65);

  my_graph.InsertEdge(1, 1, 0, 3);
  my_graph.InsertEdge(1, 1, 0, 4);
  my_graph.InsertEdge(1, 1, 0, 2);
  my_graph.InsertEdge(1, 1, 2, 5);
  my_graph.InsertEdge(1, 1, 3, 1);
  my_graph.InsertEdge(1, 1, 1, 4);
  my_graph.InsertEdge(1, 1, 1, 4);
  my_graph.InsertEdge(1, 1, 4, 3);

  my_graph.InsertEdge(1, 1, 6, 7);
  my_graph.InsertEdge(1, 1, 6, 8);
  my_graph.InsertEdge(1, 1, 8, 9);
  my_graph.InsertEdge(1, 1, 7, 10);
  my_graph.InsertEdge(1, 1, 7, 11);
  my_graph.InsertEdge(1, 1, 10, 11);
  my_graph.InsertEdge(1, 1, 11, 9);

  my_graph.PrintAllEdge('e');

  LOG(INFO) << "bfs:";
  int clock = 0;
  sstl::BfsTraverser::Traverse(
      &my_graph, 0, &clock, [](const int& data) { LOG(INFO) << data; });

  my_graph.PrintAllEdge('s');

  LOG(INFO) << "bfs for all connected field";
  sstl::BfsTraverser::Traverse(
      &my_graph, [](const int& data) { LOG(INFO) << data; });

  my_graph.PrintAllEdge('s');
  my_graph.PrintAllVertex();


  LOG(INFO) << "dfs:";
  int clock2 = 0;
  my_graph.ResetState();
  sstl::DFSTraverser::Traverse(
      &my_graph, 0, &clock2, [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "dfs for all connected field:";
  sstl::DFSTraverser::Traverse(
      &my_graph, [](const int& data) { LOG(INFO) << data; });
  my_graph.PrintAllVertex();
  my_graph.PrintAllEdge('s');
}
