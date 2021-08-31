/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_reverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"
#include "simple_stl/utility/utility.h"

namespace sstl {
struct VectorReverser {
  // reverse in [start, end)
  template <typename DataType>
  static void Reverse(Vector<DataType>* vec, const int& start_rank,
                      const int& end_rank) {
    if (vec->Size() > 1) {
      int left_index = start_rank;
      int right_index = end_rank - 1;
      while (left_index < right_index) {
        Swap(&(*vec)[left_index], &(*vec)[right_index]);
        ++left_index;
        --right_index;
      }
    }
  }

  template <typename DataType>
  static void Reverse(Vector<DataType>* vec) {
    Reverse<DataType>(vec, 0, vec->Size());
  }
};
}  // namespace sstl
