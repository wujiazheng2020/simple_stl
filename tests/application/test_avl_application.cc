/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_bitmap_algorithm.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/application/avl_application/range_query_in_1d.h"
#include "simple_stl/container/avl_tree/avl_tree.h"

TEST(TEST_AVL_APPLICATION, TEST_1D_RANGE_QUERY) {
  sstl::AvlTree<int> my_tree;
  auto empty_vec = sstl::RangeQueryIn1d(my_tree, 5, 10);
  EXPECT_EQ(empty_vec.Empty(), true);
  my_tree.Insert(2);
  my_tree.Insert(4);
  my_tree.Insert(5);
  my_tree.Insert(6);
  my_tree.Insert(8);
  my_tree.Insert(9);
  my_tree.Insert(12);
  my_tree.Insert(21);

  LOG(INFO) << "avl_inorder:";
  sstl::InorderTraverserCommon::Visit(
      [](const int& data) { std::cout << data << ","; }, my_tree.Root());
  std::cout << std::endl;

  LOG(INFO) << "test1:";
  auto data_vec = sstl::RangeQueryIn1d(my_tree, 5, 9);
  for (int i = 0; i < data_vec.Size(); ++i) {
    LOG(INFO) << data_vec[i];
  }

  LOG(INFO) << "test2:";
  auto data_vec2 = sstl::RangeQueryIn1d(my_tree, 5, 10);
  for (int i = 0; i < data_vec2.Size(); ++i) {
    LOG(INFO) << data_vec2[i];
  }

  LOG(INFO) << "test3:";
  auto data_vec3 = sstl::RangeQueryIn1d(my_tree, 3, 10);
  for (int i = 0; i < data_vec3.Size(); ++i) {
    LOG(INFO) << data_vec3[i];
  }
}
