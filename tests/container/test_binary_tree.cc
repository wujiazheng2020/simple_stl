/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_bitmap.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/binary_tree/binary_tree.h"

TEST(TEST_BINART_TREE, TestBinaryTreeNode) {
  sstl::BinaryTreeNode<int> my_tree_node;
  EXPECT_EQ(my_tree_node.InsertAsLeftChild(5)->data, 5);
  EXPECT_EQ(my_tree_node.left_child->data, 5);
  EXPECT_EQ(my_tree_node.InsertAsRightChild(6)->data, 6);
  EXPECT_EQ(my_tree_node.right_child->data, 6);
  EXPECT_EQ(my_tree_node.Size(), 3);
  EXPECT_EQ(my_tree_node.InsertAsRightChild(6), nullptr);
  EXPECT_EQ(my_tree_node.InsertAsLeftChild(5), nullptr);

  my_tree_node.left_child->InsertAsLeftChild(4);

  my_tree_node.left_child->left_child->InsertAsRightChild(6);
  EXPECT_EQ(my_tree_node.Size(), 5);
}

TEST(TEST_BINART_TREE, TestBinaryTreeBasic) {
  sstl::BinaryTree<int>* my_tree = new sstl::BinaryTree<int>();
  EXPECT_EQ(my_tree->Empty(), true);

  my_tree->InsertAsRoot(5);
  EXPECT_EQ(my_tree->InsertAsRoot(5), nullptr);
  EXPECT_EQ(sstl::BinaryTreeNodeUtils::IsRootNode(my_tree->Root()), true);
  EXPECT_EQ(my_tree->Root()->height, 0);
  my_tree->InsertAsLeftChild(my_tree->Root(), 6);
  my_tree->InsertAsRightChild(my_tree->Root(), 8);
  EXPECT_EQ(my_tree->Root()->height, 1);
  EXPECT_EQ(my_tree->Empty(), false);
  EXPECT_EQ(my_tree->Size(), 3);
  bool is_left_child =
      sstl::BinaryTreeNodeUtils::IsLeftChild(my_tree->Root()->right_child);
  EXPECT_EQ(is_left_child, false);
  is_left_child =
      sstl::BinaryTreeNodeUtils::IsLeftChild(my_tree->Root()->left_child);
  EXPECT_EQ(is_left_child, true);

  my_tree->InsertAsRightChild(my_tree->Root()->left_child, 12);
  my_tree->InsertAsLeftChild(my_tree->Root()->left_child, 11);

  my_tree->InsertAsRightChild(my_tree->Root()->right_child, 21);
  my_tree->InsertAsLeftChild(my_tree->Root()->right_child, 22);
  EXPECT_EQ(my_tree->Size(), 7);
  EXPECT_EQ(my_tree->Root()->height, 2);

  sstl::BinaryTree<int>* my_tree2 = new sstl::BinaryTree<int>();
  my_tree2->InsertAsRoot(28);
  my_tree2->AttachAsLeftChild(my_tree2->Root(), my_tree);
  EXPECT_EQ(my_tree2->Size(), 8);

  sstl::BinaryTree<int>* my_tree3 = new sstl::BinaryTree<int>();
  my_tree3->InsertAsRoot(29);
  my_tree3->InsertAsLeftChild(my_tree3->Root(), 89);
  my_tree3->InsertAsRightChild(my_tree3->Root(), 778);

  my_tree2->AttachAsRightChild(my_tree2->Root(), my_tree3);
  EXPECT_EQ(my_tree2->Size(), 11);
  EXPECT_EQ(my_tree2->Root()->height, 3);

  sstl::BinaryTree<int>* my_tree4 =
      my_tree->Secede(my_tree->Root()->left_child);
  EXPECT_EQ(my_tree4->Size(), 3);
  EXPECT_EQ(my_tree->Size(), 4);

  EXPECT_EQ(my_tree->Remove(my_tree->Root()->right_child), 3);
  EXPECT_EQ(my_tree->Size(), 1);
  EXPECT_EQ(my_tree->Remove(my_tree->Root()), 1);
  EXPECT_EQ(my_tree->Size(), 0);

  EXPECT_EQ(my_tree2->Remove(my_tree2->Root()->right_child), 3);
  delete my_tree;
}
