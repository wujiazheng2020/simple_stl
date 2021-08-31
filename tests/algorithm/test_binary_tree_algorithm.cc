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

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_bad.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/level_traverse/level_traverser.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/postorder_traverse/postorder_traverser_bad.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/postorder_traverse/postorder_traverser_common.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/preorder_traverse/preorder_traverser_bad.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/preorder_traverse/preorder_traverser_classic.h"
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/preorder_traverse/preorder_traverser_common.h"
#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/binary_tree/binary_tree_factory/binary_tree_factory.h"
#include "simple_stl/container/vector/vector.h"

TEST(TEST_BINART_TREE_ALGORITHM, Test_Tree_Traverse) {
  sstl::BinaryTree<int>* my_tree = new sstl::BinaryTree<int>();
  my_tree->InsertAsRoot(5);
  my_tree->InsertAsLeftChild(my_tree->Root(), 6);
  my_tree->InsertAsRightChild(my_tree->Root(), 8);

  my_tree->InsertAsLeftChild(my_tree->Root()->left_child, 11);
  my_tree->InsertAsRightChild(my_tree->Root()->left_child, 12);

  my_tree->InsertAsLeftChild(my_tree->Root()->right_child, 22);
  my_tree->InsertAsRightChild(my_tree->Root()->right_child, 21);

  my_tree->InsertAsRightChild(my_tree->Root()->right_child->left_child, 27);

  sstl::PreorderTraverserBad::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root()->left_child);

  LOG(INFO) << "Preorder_seq:";
  sstl::PreorderTraverserBad::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Preorder_classic_seq:";
  sstl::PreorderTraverserClassic::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Preorder_common_seq:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Inorder_seq:";
  sstl::InorderTraverserBad::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Inorder_common:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Inorder_single_visit:";
  auto my_node = my_tree->Root()->left_child->left_child;
  while (my_node) {
    LOG(INFO) << my_node->data;
    my_node = my_node->Succ();
  }

  LOG(INFO) << "Postorder_seq:";
  sstl::PostorderTraverserBad::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "Postorder_seq_common:";
  sstl::PostorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_tree->Root());

  LOG(INFO) << "level_traverse:";
  sstl::LevelTraverser::Visit([](const int& data) { LOG(INFO) << data; },
                                    my_tree->Root());
}

TEST(TEST_BINART_TREE_ALGORITHM, Test_Tree_Build) {
  sstl::BinaryTree<int>* my_tree = new sstl::BinaryTree<int>();
  my_tree->InsertAsRoot(5);
  my_tree->InsertAsLeftChild(my_tree->Root(), 6);
  my_tree->InsertAsRightChild(my_tree->Root(), 8);

  my_tree->InsertAsLeftChild(my_tree->Root()->left_child, 11);
  my_tree->InsertAsRightChild(my_tree->Root()->left_child, 12);

  my_tree->InsertAsLeftChild(my_tree->Root()->right_child, 22);
  my_tree->InsertAsRightChild(my_tree->Root()->right_child, 21);

  my_tree->InsertAsRightChild(my_tree->Root()->right_child->left_child, 27);

  sstl::Vector<int> pre_sequence;
  sstl::PreorderTraverserCommon::Visit(
      [&pre_sequence](const int& data) { pre_sequence.PushBack(data); },
      my_tree->Root());

  sstl::Vector<int> inorder_sequence;
  sstl::InorderTraverserCommon::Visit(
      [&inorder_sequence](const int& data) { inorder_sequence.PushBack(data); },
      my_tree->Root());

  sstl::BinaryTree<int>* my_build_tree =
      sstl::BinaryTreeFactory::CreateBinaryTree<int>();
  EXPECT_EQ(my_build_tree->Size(), 0);

  sstl::BinaryTree<int>* my_build_tree2 =
      sstl::BinaryTreeFactory::CreateBinaryTree<
          sstl::PreorderInorderBuilder>(pre_sequence, inorder_sequence);
  EXPECT_EQ(my_build_tree2->Size(), inorder_sequence.Size());

  LOG(INFO) << "after rebuild:";
  sstl::PostorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_build_tree2->Root());

  sstl::Vector<int> empty_vec;
  auto tree_c1 = sstl::BinaryTreeFactory::CreateBinaryTree<
      sstl::PreorderInorderBuilder>(empty_vec, inorder_sequence);
  EXPECT_EQ(tree_c1, nullptr);

  sstl::Vector<int> postorder_sequence;
  sstl::PostorderTraverserCommon::Visit(
      [&postorder_sequence](const int& data) {
        postorder_sequence.PushBack(data);
      },
      my_build_tree2->Root());

  sstl::BinaryTree<int>* my_build_tree3 =
      sstl::BinaryTreeFactory::CreateBinaryTree<
          sstl::PostorderInorderBuilder>(postorder_sequence,
                                               inorder_sequence);
  EXPECT_EQ(my_build_tree3->Size(), inorder_sequence.Size());

  LOG(INFO) << "after rebuild2:";
  sstl::PreorderTraverserCommon::Visit(
      [](const int& data) { LOG(INFO) << data; }, my_build_tree3->Root());

  auto tree_c4 = sstl::BinaryTreeFactory::CreateBinaryTree<
      sstl::PostorderInorderBuilder>(empty_vec, inorder_sequence);
  EXPECT_EQ(tree_c4, nullptr);
}
