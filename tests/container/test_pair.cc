/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_list.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/pair/pair.h"

TEST(TEST_PAIR, TEST_PAIR_BASIC) {
  sstl::Pair<int, double> pair = sstl::MakePair(1, 0.1);
  EXPECT_EQ(pair.first, 1);
  EXPECT_EQ(pair.second, 0.1);
}
