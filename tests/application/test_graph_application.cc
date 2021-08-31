/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_graph_application.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/application/graph_application/biconnected_related/biconnected_decomposite.h"
#include "simple_stl/application/graph_application/min_span_tree_related/kruskal_mst/kruskal_mst.h"
#include "simple_stl/application/graph_application/min_span_tree_related/prim_mst/prim_mst.h"
#include "simple_stl/application/graph_application/shortest_path_related/dijkstra_search/dijkstra_search.h"
#include "simple_stl/application/graph_application/shortest_path_related/floyd_iterative/floyd_iterative.h"
#include "simple_stl/application/graph_application/topo_sort/zero_in_topo_sorter.h"
#include "simple_stl/application/graph_application/topo_sort/zero_out_topo_sorter.h"

static int CharToInt(const char& my_char) { return my_char - 'A'; }

TEST(TEST_GRAPH_APPLICATION, TOPO_SORTER) {
  sstl::GraphMatrix<int, int>* my_graph = new sstl::GraphMatrix<int, int>();
  my_graph->InsertVertex(5);
  my_graph->InsertVertex(6);
  my_graph->InsertVertex(7);
  my_graph->InsertVertex(8);
  my_graph->InsertVertex(9);
  my_graph->InsertVertex(7);
  my_graph->InsertVertex(9);
  my_graph->InsertVertex(10);
  my_graph->InsertVertex(11);
  my_graph->InsertVertex(65);
  my_graph->InsertVertex(65);
  my_graph->InsertVertex(65);

  my_graph->InsertEdge(1, 1, 0, 3);
  my_graph->InsertEdge(1, 1, 0, 4);
  my_graph->InsertEdge(1, 1, 0, 2);
  my_graph->InsertEdge(1, 1, 2, 5);
  my_graph->InsertEdge(1, 1, 3, 1);
  my_graph->InsertEdge(1, 1, 4, 3);

  my_graph->InsertEdge(1, 1, 6, 7);
  my_graph->InsertEdge(1, 1, 6, 8);
  my_graph->InsertEdge(1, 1, 8, 9);
  my_graph->InsertEdge(1, 1, 7, 10);
  my_graph->InsertEdge(1, 1, 7, 11);
  my_graph->InsertEdge(1, 1, 10, 11);
  my_graph->PrintAllEdge('e');

  LOG(INFO) << "after sort:";
  auto index_vec = sstl::ZeroInTopoSorter::Sort(my_graph);
  for (int i = 0; i < index_vec.Size(); ++i) {
    LOG(INFO) << index_vec[i] << std::endl;
  }
  my_graph->InsertEdge(1, 1, 11, 7);
  LOG(INFO) << "after sort2:";
  auto index_vec2 = sstl::ZeroInTopoSorter::Sort(my_graph);
  for (int i = 0; i < index_vec2.Size(); ++i) {
    LOG(INFO) << index_vec2[i] << std::endl;
  }
  EXPECT_LT(index_vec2.Size(), my_graph->GetTotalVertexSize());

  LOG(INFO) << "after sort3:";
  my_graph->RemoveEdge(11, 7);
  auto index_vec3 = sstl::ZeroOutTopoSorter::Sort(my_graph);
  for (int i = 0; i < index_vec3.Size(); ++i) {
    LOG(INFO) << index_vec3[i] << std::endl;
  }

  LOG(INFO) << "after sort4:";
  my_graph->InsertEdge(1, 1, 11, 7);
  auto index_vec4 = sstl::ZeroOutTopoSorter::Sort(my_graph);
  for (int i = 0; i < index_vec4.Size(); ++i) {
    LOG(INFO) << index_vec4[i] << std::endl;
  }
  EXPECT_LT(index_vec4.Size(), my_graph->GetTotalVertexSize());
  delete my_graph;
  my_graph = nullptr;
}

TEST(TEST_GRAPH_APPLICATION, BICONNECTED_DECOMPOSITE) {
  sstl::GraphMatrix<char, int>* my_graph = new sstl::GraphMatrix<char, int>();
  my_graph->InsertVertex('A');  // 0
  my_graph->InsertVertex('B');  // 1
  my_graph->InsertVertex('C');  // 2
  my_graph->InsertVertex('D');  // 3
  my_graph->InsertVertex('E');  // 4
  my_graph->InsertVertex('F');  // 5
  my_graph->InsertVertex('G');  // 6
  my_graph->InsertVertex('H');  // 7
  my_graph->InsertVertex('I');  // 8
  my_graph->InsertVertex('J');  // 9
  my_graph->InsertVertex('K');  // 10
  my_graph->InsertVertex('L');  // 11

  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('E'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('A'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('I'));
  my_graph->InsertEdge(1, 1, CharToInt('I'), CharToInt('E'));
  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('B'));
  my_graph->InsertEdge(1, 1, CharToInt('B'), CharToInt('A'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('E'));
  my_graph->InsertEdge(1, 1, CharToInt('I'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('I'));
  my_graph->InsertEdge(1, 1, CharToInt('B'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('B'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('J'));
  my_graph->InsertEdge(1, 1, CharToInt('J'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('F'));

  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('D'));
  my_graph->InsertEdge(1, 1, CharToInt('D'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('H'));
  my_graph->InsertEdge(1, 1, CharToInt('H'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('K'), CharToInt('L'));
  my_graph->InsertEdge(1, 1, CharToInt('L'), CharToInt('K'));
  my_graph->InsertEdge(1, 1, CharToInt('D'), CharToInt('H'));
  my_graph->InsertEdge(1, 1, CharToInt('H'), CharToInt('D'));

  my_graph->PrintAllEdge('e');

  auto bcc_vec = sstl::BiconnectedDecomposite::Decomposite(my_graph);

  for (int i = 0; i < bcc_vec.Size(); ++i) {
    for (int j = 0; j < bcc_vec[i]->Size(); ++j) {
      std::cout << my_graph->VertexData(bcc_vec[i]->Get(j)) << " ,";
    }
    std::cout << std::endl;
  }

  delete my_graph;
  my_graph = nullptr;
}

TEST(TEST_GRAPH_APPLICATION, TEST_DIJKSTRA) {
  sstl::GraphMatrix<char, int>* my_graph = new sstl::GraphMatrix<char, int>();
  my_graph->InsertVertex('A');  // 0
  my_graph->InsertVertex('B');  // 1
  my_graph->InsertVertex('C');  // 2
  my_graph->InsertVertex('D');  // 3
  my_graph->InsertVertex('E');  // 4
  my_graph->InsertVertex('F');  // 5
  my_graph->InsertVertex('G');  // 6

  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('B'));
  my_graph->InsertEdge(1, 1, CharToInt('B'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('D'));
  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('D'));
  my_graph->InsertEdge(1, 1, CharToInt('D'), CharToInt('E'));
  my_graph->InsertEdge(1, 100, CharToInt('D'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('G'));

  LOG(INFO) << "dijkstra:";
  sstl::DijkstraSearch::Traverse(my_graph, 0, 6, [my_graph](const int& index) {
    LOG(INFO) << my_graph->VertexData(index);
  });

  LOG(INFO) << "print path";
  int now_index = 6;
  while (now_index != 0) {
    LOG(INFO) << my_graph->VertexData(now_index);
    now_index = my_graph->VertexParent(now_index);
  }
  LOG(INFO) << my_graph->VertexData(now_index);
}

TEST(TEST_GRAPH_APPLICATION, TEST_FLOYD) {
  sstl::GraphMatrix<char, int>* my_graph = new sstl::GraphMatrix<char, int>();
  my_graph->InsertVertex('A');  // 0
  my_graph->InsertVertex('B');  // 1
  my_graph->InsertVertex('C');  // 2
  my_graph->InsertVertex('D');  // 3
  my_graph->InsertVertex('E');  // 4
  my_graph->InsertVertex('F');  // 5
  my_graph->InsertVertex('G');  // 6

  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('B'));
  my_graph->InsertEdge(1, 1, CharToInt('B'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('D'));
  my_graph->InsertEdge(1, 1, CharToInt('A'), CharToInt('D'));
  my_graph->InsertEdge(1, 1, CharToInt('D'), CharToInt('E'));
  my_graph->InsertEdge(1, 100, CharToInt('D'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('F'));
  my_graph->InsertEdge(1, 1, CharToInt('F'), CharToInt('G'));

  LOG(INFO) << "floyd:";
  auto shortest_matrix = sstl::FloydIterative::Call(*my_graph);

  int n = shortest_matrix.Size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (shortest_matrix[i][j] < 10) {
        std::cout << shortest_matrix[i][j];
      } else {
        std::cout << 'x';
      }
      std::cout << " ,";
    }
    std::cout << std::endl;
  }
}

TEST(TEST_GRAPH_APPLICATION, TEST_PRIM) {
  sstl::GraphMatrix<char, int>* my_graph = new sstl::GraphMatrix<char, int>();
  my_graph->InsertVertex('A');  // 0
  my_graph->InsertVertex('B');  // 1
  my_graph->InsertVertex('C');  // 2
  my_graph->InsertVertex('D');  // 3
  my_graph->InsertVertex('E');  // 4
  my_graph->InsertVertex('F');  // 5
  my_graph->InsertVertex('G');  // 6
  my_graph->InsertVertex('H');  // 7

  my_graph->InsertEdge(1, 4, CharToInt('A'), CharToInt('B'));
  my_graph->InsertEdge(1, 4, CharToInt('B'), CharToInt('A'));
  my_graph->InsertEdge(1, 12, CharToInt('B'), CharToInt('C'));
  my_graph->InsertEdge(1, 12, CharToInt('C'), CharToInt('B'));

  my_graph->InsertEdge(1, 7, CharToInt('A'), CharToInt('G'));
  my_graph->InsertEdge(1, 7, CharToInt('G'), CharToInt('A'));
  my_graph->InsertEdge(1, 6, CharToInt('A'), CharToInt('D'));
  my_graph->InsertEdge(1, 6, CharToInt('D'), CharToInt('A'));
  my_graph->InsertEdge(1, 9, CharToInt('C'), CharToInt('D'));
  my_graph->InsertEdge(1, 9, CharToInt('D'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('E'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('C'));
  my_graph->InsertEdge(1, 2, CharToInt('C'), CharToInt('F'));
  my_graph->InsertEdge(1, 2, CharToInt('F'), CharToInt('C'));
  my_graph->InsertEdge(1, 10, CharToInt('C'), CharToInt('H'));
  my_graph->InsertEdge(1, 10, CharToInt('H'), CharToInt('C'));

  my_graph->InsertEdge(1, 13, CharToInt('D'), CharToInt('E'));
  my_graph->InsertEdge(1, 13, CharToInt('E'), CharToInt('D'));
  my_graph->InsertEdge(1, 5, CharToInt('E'), CharToInt('F'));
  my_graph->InsertEdge(1, 5, CharToInt('F'), CharToInt('E'));

  my_graph->InsertEdge(1, 2, CharToInt('D'), CharToInt('G'));
  my_graph->InsertEdge(1, 2, CharToInt('G'), CharToInt('D'));
  my_graph->InsertEdge(1, 11, CharToInt('E'), CharToInt('G'));
  my_graph->InsertEdge(1, 11, CharToInt('G'), CharToInt('E'));
  my_graph->InsertEdge(1, 8, CharToInt('E'), CharToInt('H'));
  my_graph->InsertEdge(1, 8, CharToInt('H'), CharToInt('E'));
  my_graph->InsertEdge(1, 7, CharToInt('F'), CharToInt('H'));
  my_graph->InsertEdge(1, 7, CharToInt('H'), CharToInt('F'));

  my_graph->InsertEdge(1, 14, CharToInt('G'), CharToInt('H'));
  my_graph->InsertEdge(1, 14, CharToInt('H'), CharToInt('G'));

  LOG(INFO) << "prim:";
  sstl::PrimMST::Traverse(my_graph, 0, 7, [my_graph](const int& index) {
    LOG(INFO) << my_graph->VertexData(index);
  });
  // you can reconstruct the whole tree easily,
  // but it may be not the binary tree
  // 1. construct N tree
  // 2. if parent = i, attach it to the tree i in order
  // 3. till rest just single tree
  my_graph->PrintAllVertex();
}

TEST(TEST_GRAPH_APPLICATION, TEST_Kruskal) {
  sstl::GraphMatrix<char, int>* my_graph = new sstl::GraphMatrix<char, int>();
  my_graph->InsertVertex('A');  // 0
  my_graph->InsertVertex('B');  // 1
  my_graph->InsertVertex('C');  // 2
  my_graph->InsertVertex('D');  // 3
  my_graph->InsertVertex('E');  // 4
  my_graph->InsertVertex('F');  // 5
  my_graph->InsertVertex('G');  // 6
  my_graph->InsertVertex('H');  // 7

  my_graph->InsertEdge(1, 4, CharToInt('A'), CharToInt('B'));
  my_graph->InsertEdge(1, 4, CharToInt('B'), CharToInt('A'));
  my_graph->InsertEdge(1, 12, CharToInt('B'), CharToInt('C'));
  my_graph->InsertEdge(1, 12, CharToInt('C'), CharToInt('B'));

  my_graph->InsertEdge(1, 7, CharToInt('A'), CharToInt('G'));
  my_graph->InsertEdge(1, 7, CharToInt('G'), CharToInt('A'));
  my_graph->InsertEdge(1, 6, CharToInt('A'), CharToInt('D'));
  my_graph->InsertEdge(1, 6, CharToInt('D'), CharToInt('A'));
  my_graph->InsertEdge(1, 9, CharToInt('C'), CharToInt('D'));
  my_graph->InsertEdge(1, 9, CharToInt('D'), CharToInt('C'));
  my_graph->InsertEdge(1, 1, CharToInt('C'), CharToInt('E'));
  my_graph->InsertEdge(1, 1, CharToInt('E'), CharToInt('C'));
  my_graph->InsertEdge(1, 2, CharToInt('C'), CharToInt('F'));
  my_graph->InsertEdge(1, 2, CharToInt('F'), CharToInt('C'));
  my_graph->InsertEdge(1, 10, CharToInt('C'), CharToInt('H'));
  my_graph->InsertEdge(1, 10, CharToInt('H'), CharToInt('C'));

  my_graph->InsertEdge(1, 13, CharToInt('D'), CharToInt('E'));
  my_graph->InsertEdge(1, 13, CharToInt('E'), CharToInt('D'));
  my_graph->InsertEdge(1, 5, CharToInt('E'), CharToInt('F'));
  my_graph->InsertEdge(1, 5, CharToInt('F'), CharToInt('E'));

  my_graph->InsertEdge(1, 2, CharToInt('D'), CharToInt('G'));
  my_graph->InsertEdge(1, 2, CharToInt('G'), CharToInt('D'));
  my_graph->InsertEdge(1, 11, CharToInt('E'), CharToInt('G'));
  my_graph->InsertEdge(1, 11, CharToInt('G'), CharToInt('E'));
  my_graph->InsertEdge(1, 8, CharToInt('E'), CharToInt('H'));
  my_graph->InsertEdge(1, 8, CharToInt('H'), CharToInt('E'));
  my_graph->InsertEdge(1, 7, CharToInt('F'), CharToInt('H'));
  my_graph->InsertEdge(1, 7, CharToInt('H'), CharToInt('F'));

  my_graph->InsertEdge(1, 14, CharToInt('G'), CharToInt('H'));
  my_graph->InsertEdge(1, 14, CharToInt('H'), CharToInt('G'));

  LOG(INFO) << "krustal_undirect";
  sstl::KruskalMST::Call(my_graph, true, [my_graph](const int& index) {
    LOG(INFO) << my_graph->VertexData(index);
  });

  LOG(INFO) << "krustal_direct";
  sstl::KruskalMST::Call(my_graph, false, [my_graph](const int& index) {
    LOG(INFO) << my_graph->VertexData(index);
  });

  my_graph->PrintAllVertex();
}
