/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_select_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2)
struct VectorSelectSort {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    for (int i = end_rank - 1; i >= start_rank; --i) {
      int max_index = i;
      for (int j = start_rank; j < i; ++j) {
        // for stable
        if ((*vec)[max_index] < (*vec)[j] ||
            (*vec)[max_index] == (*vec)[j]) {
          max_index = j;
        }
      }
      if (max_index != i) {
        DataType tmp = (*vec)[max_index];
        (*vec)[max_index] = (*vec)[i];
        (*vec)[i] = tmp;
      }
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};
}  // namespace sstl
