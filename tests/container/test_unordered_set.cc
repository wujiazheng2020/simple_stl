/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_unordered_set.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/unordered_set/unordered_set.h"
#include "simple_stl/container/avl_tree/avl_tree.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/splay_tree/splay_tree.h"

template <typename SetType>
void TestForAllAPI(SetType* set) {
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(set->Insert(i), true);
    EXPECT_EQ(set->Insert(i), false);
  }
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(set->Search(i), true);
  }
  EXPECT_EQ(set->Size(), 100);

  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(set->Remove(i), true);
    EXPECT_EQ(set->Remove(i), false);
  }
  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(set->Search(i), false);
  }
  EXPECT_EQ(set->Size(), 50);

  for (int i = 50; i < 100; ++i) {
    EXPECT_EQ(set->Search(i), true);
  }
  delete set;
}

TEST(TEST_UNORDERED_SET, TEST_UNORDERED_ALL) {
  TestForAllAPI(new sstl::UnorderedSet<int, 3, sstl::RedBlackTree>);
  TestForAllAPI(new sstl::UnorderedSet<int, 3, sstl::BinarySearchTree>);
  TestForAllAPI(new sstl::UnorderedSet<int, 3, sstl::AvlTree>);
  TestForAllAPI(new sstl::UnorderedSet<int, 3, sstl::SplayTree>);
  TestForAllAPI(new sstl::UnorderedSet<int>);
}
