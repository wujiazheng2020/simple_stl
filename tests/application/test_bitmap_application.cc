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

#include <vector>

#include "simple_stl/application/bitmap_application/calculate_prime.h"

static const std::vector<int> prime_vec =
    sstl::CalculatePrimeBelowN<10000>();

TEST(BIT_MAP, BitMapBasic) {
  for (uint i = 1; i < prime_vec.size(); ++i) {
    std::cout << prime_vec[i] << " ";
    if (i % 15 == 0) {
      std::cout << std::endl;
    }
  }
}
