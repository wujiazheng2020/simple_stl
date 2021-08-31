/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_map.cc
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
#include "simple_stl/container/map/map.h"
#include "simple_stl/container/splay_tree/splay_tree.h"

template <template <typename Datatype> class Container>
void TestAllOperate(sstl::Map<int, int, Container>* map) {
  for (int i = 0; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    map->Insert(sstl::MakePair(un_repeat_random_num, un_repeat_random_num / 2));
  }
  EXPECT_EQ(map->Size(), 200);

  for (int i = 0; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    EXPECT_EQ(map->Search(un_repeat_random_num)->data.first,
              un_repeat_random_num);
    EXPECT_EQ(map->Search(un_repeat_random_num)->data.second,
              un_repeat_random_num / 2);
  }

  for (int i = 0; i < 150; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    map->Remove(un_repeat_random_num);
  }
  EXPECT_EQ(map->Size(), 50);

  for (int i = 150; i < 200; i++) {
    int un_repeat_random_num =
        std::floor(1e5 * sin(i * 123 - 59 * i * i + 20 * i * i * i));
    map->Remove(un_repeat_random_num);
  }
  EXPECT_EQ(map->Size(), 0);
  delete map;
}

TEST(TEST_Map, TEST_ALL) {
  TestAllOperate(new sstl::Map<int, int, sstl::BinarySearchTree>());
  TestAllOperate(new sstl::Map<int, int, sstl::RedBlackTree>());
  TestAllOperate(new sstl::Map<int, int, sstl::AvlTree>());
  TestAllOperate(new sstl::Map<int, int, sstl::SplayTree>());
  TestAllOperate(new sstl::Map<int, int>());
}
