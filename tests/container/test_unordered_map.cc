/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_unordered_map.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/avl_tree/avl_tree.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/splay_tree/splay_tree.h"
#include "simple_stl/container/unordered_map/unordered_map.h"

template <typename MapType>
void TestForAllAPI(MapType* map) {
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(map->Insert(sstl::MakePair(i, i / 2)), true);
    EXPECT_EQ(map->Insert(sstl::MakePair(i, i / 2)), false);
  }
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(map->Search(i)->second, i / 2);
  }
  EXPECT_EQ(map->Size(), 100);

  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(map->Remove(i), true);
    EXPECT_EQ(map->Remove(i), false);
  }
  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(map->Search(i), nullptr);
  }
  EXPECT_EQ(map->Size(), 50);

  for (int i = 50; i < 100; ++i) {
    EXPECT_EQ(map->Search(i)->second, i / 2);
  }
  delete map;
}

TEST(TEST_UNORDERED_MAP, TEST_ALL_API) {
  TestForAllAPI(new sstl::UnorderedMap<int, int, 3, sstl::RedBlackTree>);
  TestForAllAPI(new sstl::UnorderedMap<int, int, 3, sstl::BinarySearchTree>);
  TestForAllAPI(new sstl::UnorderedMap<int, int, 3, sstl::AvlTree>);
  TestForAllAPI(new sstl::UnorderedMap<int, int, 3, sstl::SplayTree>);
  TestForAllAPI(new sstl::UnorderedMap<int, int>);
}
