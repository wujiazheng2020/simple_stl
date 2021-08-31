/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_bubble_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2) corresponding with the inverse pair
struct VectorBubbleSort {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    int no_ordered = end_rank - 1;
    // means [0, no_ordered) is not in ordered
    for (int i = end_rank - 1; i > start_rank; i = no_ordered) {
      for (int j = start_rank; j < i; ++j) {
        // confirm stable
        if ((*vec)[j + 1] < (*vec)[j]) {
          DataType tmp = (*vec)[j];
          (*vec)[j] = (*vec)[j + 1];
          (*vec)[j + 1] = tmp;
          no_ordered = j;
        }
      }
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};

}  // namespace sstl
