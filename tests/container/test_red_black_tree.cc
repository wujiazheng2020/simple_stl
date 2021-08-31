/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_red_black_tree.cc
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
#include "simple_stl/container/red_black_tree/red_black_tree.h"

template <typename NodeType>
void CatNodeInfo(NodeType* my_node) {
  std::cout << "#data:" << my_node->data << " ,color:" << my_node->color
            << " ,height:" << my_node->height << std::endl;
}

template <typename NodeType>
void InorderTestVisit(NodeType* node) {
  if (!node) {
    return;
  }
  InorderTestVisit(node->left_child);
  CatNodeInfo(node);
  if (node->color == sstl::kRedColor) {
    if (node->parent) {
      EXPECT_EQ(node->parent->color, sstl::kBlackColor);
    }
    if (node->left_child) {
      EXPECT_EQ(node->left_child->color, sstl::kBlackColor);
    }
    if (node->right_child) {
      EXPECT_EQ(node->right_child->color, sstl::kBlackColor);
    }
  }
  InorderTestVisit(node->right_child);
}

TEST(TEST_RED_BLACK_TREE, TEST_RED_BLACK_TREE_BASIC) {
  sstl::RedBlackTree<int> red_black_tree;

  red_black_tree.Insert(5);
  red_black_tree.Insert(6);
  red_black_tree.Insert(7);

  std::cout << "insert1:";
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  std::cout << "insert2:" << std::endl;
  red_black_tree.Insert(8);
  red_black_tree.Insert(4);
  red_black_tree.Insert(3);
  red_black_tree.Insert(3);

  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  std::cout << "remove double son" << std::endl;
  red_black_tree.Remove(4);
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  std::cout << "remove root" << std::endl;
  red_black_tree.Remove(6);
  red_black_tree.Remove(6);
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  LOG(INFO) << "remove root:";
  red_black_tree.Remove(7);
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  LOG(INFO) << "remove left:";
  red_black_tree.Remove(8);
  red_black_tree.Remove(5);
  red_black_tree.Remove(3);
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, red_black_tree.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree.Root());

  sstl::RedBlackTree<int> red_black_tree2;

  for (int i = 0; i < 200; ++i) {
    red_black_tree2.Insert(
        std::floor(1e5 * std::sin(i * 111 - 59 * i * i + 20 * i * i * i)));
  }
  InorderTestVisit(red_black_tree2.Root());
  EXPECT_EQ(red_black_tree2.Size(), 200);

  for (int i = 0; i < 180; ++i) {
    red_black_tree2.Remove(
        std::floor(1e5 * std::sin(i * 111 - 59 * i * i + 20 * i * i * i)));
  }
  InorderTestVisit(red_black_tree2.Root());
  EXPECT_EQ(red_black_tree2.Size(), 20);

  sstl::RedBlackTree<int> red_black_tree3;
  red_black_tree3.InsertAsRoot(5);
  red_black_tree3.Root()->color = sstl::kBlackColor;

  red_black_tree3.InsertAsLeftChild(red_black_tree3.Root(), 3);

  red_black_tree3.InsertAsRightChild(red_black_tree3.Root()->left_child, 4);
  red_black_tree3.Root()->left_child->right_child->color = sstl::kBlackColor;

  red_black_tree3.InsertAsLeftChild(red_black_tree3.Root()->left_child, 2);
  red_black_tree3.Root()->left_child->left_child->color = sstl::kBlackColor;

  red_black_tree3.InsertAsRightChild(red_black_tree3.Root(), 6);
  red_black_tree3.Root()->right_child->color = sstl::kBlackColor;

  red_black_tree3.Root()->height = 1;
  red_black_tree3.Root()->left_child->height = 0;
  red_black_tree3.Root()->left_child->right_child->height = 0;
  red_black_tree3.Root()->left_child->left_child->height = 0;
  red_black_tree3.Root()->right_child->height = 0;
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; },
      red_black_tree3.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; },
      red_black_tree3.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree3.Root());

  red_black_tree3.Remove(6);
  LOG(INFO) << "after remove:";
  LOG(INFO) << "rbt_preorder:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; },
      red_black_tree3.Root());
  std::cout << std::endl;

  LOG(INFO) << "rbt_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; },
      red_black_tree3.Root());
  std::cout << std::endl;
  InorderTestVisit(red_black_tree3.Root());
}
