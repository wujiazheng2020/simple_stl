/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: calculate_prime.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <vector>

#include "simple_stl/container/bitmap/bitmap.h"

namespace sstl {
// calculate prime using eratosthenes
// compute in compile time
// time complexity O(nlogn)
template <int N>
constexpr std::vector<int> CalculatePrimeBelowN() {
  // maybe overflow
  Bitmap bitmap(N);
  std::vector<int> prime_vec;

  bitmap.Set(0);
  bitmap.Set(1);
  for (int i = 2; i < N; ++i) {
    if (!bitmap.Test(i)) {
      for (int j = 2 * i; j < N; j += i) {
        bitmap.Set(j);
      }
    }
  }

  for (int i = 1; i < N; ++i) {
    if (!bitmap.Test(i)) {
      prime_vec.emplace_back(i);
    }
  }
  return prime_vec;
}

}  // namespace sstl
