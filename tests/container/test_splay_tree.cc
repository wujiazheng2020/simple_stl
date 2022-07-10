/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_avl_tree.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <cmath>

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/preorder_traverse/preorder_traverser_common.h"
#include "simple_stl/container/splay_tree/splay_tree.h"

TEST(TEST_SPLAY_TREE, TEST_SPLAY_TREE_BASIC) {
  sstl::SplayTree<int> splay_tree;
  splay_tree.Insert(3);
  splay_tree.Insert(6);
  splay_tree.Insert(7);
  splay_tree.Insert(8);
  splay_tree.Insert(9);
  splay_tree.Insert(9);
  splay_tree.Insert(2);

  LOG(INFO) << "avl_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  splay_tree.Search(7);

  LOG(INFO) << "avl_preorder2:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder2:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  splay_tree.Insert(5);

  LOG(INFO) << "avl_preorder3:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder3:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  splay_tree.Insert(4);

  LOG(INFO) << "avl_preorder4:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder4:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  splay_tree.Remove(9);
  std::cout << "remove end" << std::endl;
  splay_tree.Remove(8);
  splay_tree.Remove(22);

  LOG(INFO) << "avl_preorder5:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder5:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  splay_tree.Remove(3);

  LOG(INFO) << "avl_preorder6:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder6:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, splay_tree.Root());
  std::cout << std::endl;

  sstl::SplayTree<int> splay_tree2;
  for (int i = 0; i < 200; ++i) {
    splay_tree2.Insert(floor(1e5 * std::sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }
  EXPECT_EQ(splay_tree2.Size(), 200);
  for (int i = 0; i < 180; ++i) {
    splay_tree2.Remove(floor(1e5 * std::sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }
  EXPECT_EQ(splay_tree2.Size(), 20);
}
