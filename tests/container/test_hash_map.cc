/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_hash_map.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/hash_map/open_hash_map.h"

TEST(TEST_HASH_MAP, OPEN_HASH_MAP) {
  // all type test leave for unordered_set
  sstl::OpenHashMap<uint32_t> hash_map;

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(hash_map.Insert(i), true);
    EXPECT_EQ(hash_map.Insert(i), false);
  }
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(hash_map.Search(i), true);
  }
  EXPECT_EQ(hash_map.Size(), 1000);

  for (int i = 0; i < 500; ++i) {
    EXPECT_EQ(hash_map.Remove(i), true);
    EXPECT_EQ(hash_map.Remove(i), false);
  }
  for (int i = 0; i < 500; ++i) {
    EXPECT_EQ(hash_map.Search(i), false);
  }

  for (int i = 500; i < 1000; ++i) {
    EXPECT_EQ(hash_map.Search(i), true);
  }
  EXPECT_EQ(hash_map.Capcity(), 11264);
  EXPECT_EQ(hash_map.Size(), 500);
}
