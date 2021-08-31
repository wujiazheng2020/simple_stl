/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_graph.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/graph/graph_matrix.h"

TEST(TEST_GRAPH, TEST_GRAPH_BASIC) {
  sstl::GraphMatrix<int, int> my_graph;

  for (int i = 0; i < 10; ++i) {
    my_graph.InsertVertex(i);
  }

  my_graph.PrintAllVertex();

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      my_graph.InsertEdge(i, i + j, i, j);
    }
  }
  my_graph.PrintAllVertex();
  my_graph.PrintAllEdge('e');
  my_graph.PrintAllEdge('w');
  my_graph.PrintAllEdge('s');
  my_graph.PrintAllEdge('d');
  my_graph.PrintAllEdge('x');
  EXPECT_EQ(my_graph.GetTotalEdgeSize(), 100);
  EXPECT_EQ(my_graph.GetTotalVertexSize(), 10);

  my_graph.RemoveVertex(5);
  my_graph.PrintAllVertex();
  my_graph.PrintAllEdge('d');
  EXPECT_EQ(my_graph.GetTotalEdgeSize(), 81);
  EXPECT_EQ(my_graph.GetTotalVertexSize(), 9);

  my_graph.RemoveEdge(2, 6);
  my_graph.PrintAllEdge('e');
  my_graph.EdgeData(1, 2) = 1;
  my_graph.EdgeWeight(1, 6) = 4;

  my_graph.VertexData(3) = 665;
  my_graph.VertexParent(1) = 2;
  my_graph.PrintAllVertex();
  EXPECT_EQ(my_graph.GetTotalEdgeSize(), 80);
  EXPECT_EQ(my_graph.GetTotalVertexSize(), 9);

  const sstl::GraphMatrix<int, int> my_graph2 = my_graph;
  EXPECT_EQ(my_graph2.EdgeData(1, 2), 1);
  EXPECT_EQ(my_graph2.EdgeStatus(1, 2), sstl::UNDETERMINED);
  EXPECT_EQ(my_graph2.VertexData(3), 665);
  EXPECT_EQ(my_graph2.VertexInDegree(6), 8);
  EXPECT_EQ(my_graph2.VertexOutDegree(2), 8);

  my_graph.ResetState();
  my_graph.PrintAllVertex();
}
