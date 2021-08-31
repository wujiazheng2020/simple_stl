/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_deduplicator.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/finder/vector_finder.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// for disordered vector
// you can use bitmap to improve the efficiency
// with bitmap you can get a average O(n) algorithm
// but it only suits for int, char, short,
// for other type you can use hash_map
// the best O(n)
// the worst O(n^2)
// return old_size - new_size
struct VectorDeduplicator {
  template <typename DataType>
  static int Deduplicate(Vector<DataType>* vec) {
    int old_size = vec->Size();
    int new_size = old_size;
    int left_i = 1;  // [0, left_i) is over
    int right_i = 1;
    while (right_i < old_size) {
      if ((VectorFinder::Find(*vec, 0, left_i, (*vec)[right_i])) < 0) {
        (*vec)[left_i] = (*vec)[right_i];
        ++left_i;
      } else {
        --new_size;
      }
      ++right_i;
    }
    vec->Remove(new_size, old_size);
    return old_size - new_size;
  }
};
}  // namespace sstl
