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
#include "simple_stl/container/avl_tree/avl_tree.h"

TEST(TEST_AVL_TREE, AVL_BASIC) {
  sstl::AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(20);
  avl_tree.Insert(30);
  avl_tree.Insert(40);
  avl_tree.Insert(50);
  avl_tree.Insert(60);
  avl_tree.Insert(70);
  avl_tree.Insert(49);
  avl_tree.Insert(48);

  LOG(INFO) << "avl_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree.Root());
  std::cout << std::endl;

  sstl::AvlTree<int> avl_tree2;
  avl_tree2.Insert(0);
  avl_tree2.Insert(4);
  avl_tree2.Insert(2);
  avl_tree2.Insert(3);
  avl_tree2.Insert(1);

  LOG(INFO) << "avl_preorder2:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree2.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder2:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree2.Root());
  std::cout << std::endl;

  sstl::AvlTree<int> avl_tree3;
  avl_tree3.Insert(3);
  avl_tree3.Insert(2);
  avl_tree3.Insert(5);
  avl_tree3.Insert(0);
  avl_tree3.Insert(1);

  LOG(INFO) << "avl_preorder3:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree3.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder3:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree3.Root());
  std::cout << std::endl;

  sstl::AvlTree<int> avl_tree4;

  for (int i = 0; i < 100; i++) {
    avl_tree4.Insert(
        std::floor(1e5 * std::sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }
  EXPECT_EQ(avl_tree4.Size(), 100);

  int old_data = -1123312;
  sstl::InorderTraverserCommon::Visit(
      [&old_data](const int& data) {
        EXPECT_LT(old_data, data);
        old_data = data;
      },
      avl_tree4.Root());

  avl_tree3.Insert(10);
  avl_tree3.Insert(19);
  avl_tree3.Insert(8);
  avl_tree3.Insert(7);

  avl_tree3.Remove(1);
  avl_tree3.Remove(7);
  avl_tree3.Remove(8);
  avl_tree3.Remove(0);

  LOG(INFO) << "avl_preorder_remove:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree3.Root());
  std::cout << std::endl;

  LOG(INFO) << "avl_inorder_remove:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, avl_tree3.Root());
  std::cout << std::endl;

  for (int i = 0; i < 80; i++) {
    avl_tree4.Remove(floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i)));
  }

  old_data = -122232321;
  sstl::InorderTraverserCommon::Visit(
      [&old_data](const int& data) {
        EXPECT_LT(old_data, data);
        old_data = data;
      },
      avl_tree4.Root());
}
