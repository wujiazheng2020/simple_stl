/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_uniquifier.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/finder/vector_finder.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// for ordered vector
// time complxity O(n)
// return old_size - new_size
// if is disordered return -2
struct VectorUniquifier {
  template <typename DataType>
  static int Uniquify(Vector<DataType>* vec) {
    if (!vec->CheckOrdered()) {
      return -2;
    }
    if (vec->Empty()) {
      return 0;
    }

    int old_size = vec->Size();
    int new_size = old_size;
    int left_i = 0;
    int right_i = 1;
    while (right_i < old_size) {
      if ((*vec)[right_i] == (*vec)[left_i]) {
        --new_size;
      } else {
        ++left_i;
        (*vec)[left_i] = (*vec)[right_i];
      }
      ++right_i;
    }
    vec->Remove(new_size, old_size);
    return old_size - new_size;
  }
};
}  // namespace sstl
