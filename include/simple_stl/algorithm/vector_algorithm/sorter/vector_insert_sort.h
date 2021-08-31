/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_insert_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2) corresponding with the inverse pair
struct VectorInsertSort {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    for (int i = start_rank + 1; i < end_rank; ++i) {
      DataType now_elem = (*vec)[i];
      int j = i - 1;
      while (j >= start_rank) {
        // for stable
        if ((*vec)[j] < now_elem || (*vec)[j] == now_elem) {
          (*vec)[j + 1] = now_elem;
          break;
        }
        (*vec)[j + 1] = (*vec)[j];
        --j;
      }
      if (j == start_rank - 1) {
        (*vec)[start_rank] = now_elem;
      }
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};

}  // namespace sstl
