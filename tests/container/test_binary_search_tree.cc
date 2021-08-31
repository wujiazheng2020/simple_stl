/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_binary_search_tree.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/preorder_traverse/preorder_traverser_common.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree.h"

TEST(TEST_BINART_SEARCH_TREE, TestBinarySearchTreeBasic) {
  sstl::BinarySearchTree<int> my_bst;
  my_bst.Insert(2);
  my_bst.Insert(14);
  my_bst.Insert(12);
  my_bst.Insert(15);
  my_bst.Insert(3);
  my_bst.Insert(4);
  my_bst.Insert(9);
  my_bst.Insert(7);
  my_bst.Insert(7);
  EXPECT_EQ(my_bst.Size(), 8);

  LOG(INFO) << "bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  LOG(INFO) << "bst_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  EXPECT_EQ(my_bst.Search(14)->data, 14);
  EXPECT_EQ(my_bst.Search(17), nullptr);

  EXPECT_EQ(my_bst.Search(13), nullptr);

  my_bst.Remove(7);
  LOG(INFO) << "remove 7 bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  my_bst.Remove(9);
  LOG(INFO) << "remove 7 9 bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  my_bst.Remove(3);
  LOG(INFO) << "remove 3 7 9 bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  my_bst.Remove(2);
  LOG(INFO) << "remove root bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  my_bst.Remove(4);
  my_bst.Remove(12);
  my_bst.Remove(77);
  my_bst.Remove(14);
  my_bst.Remove(15);
  LOG(INFO) << "remove root bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());
  EXPECT_EQ(my_bst.Size(), 0);

  my_bst.Insert(2);
  my_bst.Insert(14);
  my_bst.Insert(12);
  my_bst.Insert(15);
  my_bst.Insert(3);
  my_bst.Insert(4);
  my_bst.Insert(9);
  my_bst.Insert(7);

  my_bst.Remove(3);
  my_bst.Remove(4);
  my_bst.Remove(9);
  my_bst.Remove(7);
  my_bst.Remove(14);
  LOG(INFO) << "remove 3 4 9 7 bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_bst.Root());

  my_bst.Insert(14);
  my_bst.Insert(17);
  my_bst.Insert(18);
  my_bst.Insert(20);
  my_bst.Insert(16);

  std::cout << std::endl;
  LOG(INFO) << "bst_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, my_bst.Root());
  std::cout << std::endl;

  LOG(INFO) << "insert bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, my_bst.Root());
  std::cout << std::endl;

  std::cout << "remove15" << std::endl;
  my_bst.Remove(15);
  LOG(INFO) << "bst_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, my_bst.Root());
  std::cout << std::endl;

  LOG(INFO) << "remove bst_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, my_bst.Root());
  std::cout << std::endl;
}
