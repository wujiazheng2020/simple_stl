/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_set.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <cmath>

#include "simple_stl/container/avl_tree/avl_tree.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/set/set.h"
#include "simple_stl/container/splay_tree/splay_tree.h"

template <template <typename Datatype> class Container>
void TestAllOperate(sstl::Set<int, Container>* set) {
  for (int i = 0; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    set->Insert(un_repeat_random_num);
  }
  EXPECT_EQ(set->Size(), 200);

  for (int i = 0; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    EXPECT_EQ(set->Search(un_repeat_random_num)->data, un_repeat_random_num);
  }

  for (int i = 0; i < 150; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    set->Remove(un_repeat_random_num);
  }
  EXPECT_EQ(set->Size(), 50);

  for (int i = 150; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    set->Remove(un_repeat_random_num);
  }
  EXPECT_EQ(set->Size(), 0);
  delete set;
}

TEST(TEST_SET, TEST_ALL) {
  TestAllOperate(new sstl::Set<int, sstl::BinarySearchTree>());
  TestAllOperate(new sstl::Set<int, sstl::RedBlackTree>());
  TestAllOperate(new sstl::Set<int, sstl::AvlTree>());
  TestAllOperate(new sstl::Set<int, sstl::SplayTree>());
  TestAllOperate(new sstl::Set<int>());
}
