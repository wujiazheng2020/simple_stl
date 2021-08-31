/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_b_minus_tree.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <cmath>

#include "simple_stl/container/b_minus_tree/b_minus_tree.h"
#include "simple_stl/container/queue/queue.h"

// just for test
template <typename BNode>
void TraverseForTest(BNode* now_node) {
  sstl::Queue<BNode*> b_node_queue;
  b_node_queue.Enqueue(now_node);
  int layer = 0;
  int this_layer_total = 0;
  int last_layer_total = 0;
  while (!b_node_queue.Empty()) {
    std::cout << "L" << layer << " :";
    BNode* current_node = b_node_queue.Dequeue();
    EXPECT_LE(current_node->key_vec->Size(), 4);
    if (current_node != now_node) {
      EXPECT_GE(current_node->key_vec->Size(), 2);
    }
    for (int i = 0; i < current_node->key_vec->Size(); ++i) {
      std::cout << current_node->key_vec->Get(i) << " ,";
    }
    for (int i = 0; i < current_node->child_vec->Size(); ++i) {
      if (!current_node->child_vec->Get(i)) {
        break;
      }
      b_node_queue.Enqueue(current_node->child_vec->Get(i));
      ++this_layer_total;
    }
    if (last_layer_total == 0) {
      last_layer_total = this_layer_total;
      this_layer_total = 0;
      ++layer;
    } else {
      --last_layer_total;
    }
    std::cout << std::endl;
  }
}

TEST(TEST_B_MINUS_TREE, TEST_B_NODE) {
  sstl::BNode<int>* b_node = new sstl::BNode<int>();
  sstl::BNode<int>* b_node2 = new sstl::BNode<int>();
  sstl::BNode<int>* b_node3 = new sstl::BNode<int>(5, b_node, b_node2);

  EXPECT_EQ(b_node3->key_vec->Get(0), 5);
  delete b_node;
  delete b_node2;
  delete b_node3;
}

TEST(TEST_B_MINUS_TREE, TEST_B_MINUS_TREE_BASIC) {
  sstl::BMinusTree<int, 5>* b_tree = new sstl::BMinusTree<int, 5>();

  EXPECT_EQ(b_tree->Order(), 5);
  EXPECT_EQ(b_tree->Empty(), true);
  EXPECT_EQ(b_tree->Size(), 0);
  EXPECT_NE(b_tree->Root(), nullptr);

  b_tree->Insert(1);
  b_tree->Insert(4);
  b_tree->Insert(8);
  b_tree->Insert(10);
  b_tree->Insert(12);
  b_tree->Insert(14);
  b_tree->Insert(3);
  b_tree->Insert(16);

  std::cout << "BFS1:" << std::endl;
  TraverseForTest(b_tree->Root());

  b_tree->Insert(20);
  b_tree->Insert(5);
  b_tree->Insert(6);
  std::cout << "BFS2:" << std::endl;
  TraverseForTest(b_tree->Root());

  b_tree->Insert(21);
  b_tree->Insert(22);
  b_tree->Insert(23);
  b_tree->Insert(24);
  b_tree->Insert(25);
  std::cout << "BFS3:" << std::endl;
  TraverseForTest(b_tree->Root());

  b_tree->Insert(26);
  b_tree->Insert(26);
  std::cout << "BFS4:" << std::endl;
  TraverseForTest(b_tree->Root());

  b_tree->Remove(26);
  b_tree->Remove(99);
  std::cout << "BFS5:" << std::endl;
  TraverseForTest(b_tree->Root());

  sstl::BMinusTree<int, 5>* b_tree2 = new sstl::BMinusTree<int, 5>();
  for (int i = 0; i < 200; ++i) {
    b_tree2->Insert(
        std::floor(1e5 * std::sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }
  EXPECT_EQ(b_tree2->Size(), 200);

  for (int i = 0; i < 150; ++i) {
    b_tree2->Remove(
        std::floor(1e5 * std::sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }
  std::cout << "BFS5:" << std::endl;
  EXPECT_EQ(b_tree2->Size(), 50);
  TraverseForTest(b_tree2->Root());
  delete b_tree;
}
