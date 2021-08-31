/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_quick_sort_bad.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2) corresponding with the inverse pair
// but it is a unstable algorithm
// this version just use for benchmark
template <typename Partitioner>
struct VectorQuickSortBad {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    if (end_rank - start_rank <= 1) {
      return;
    }
    int mid_rank = Partitioner::Call(vec, start_rank, end_rank);
    Sort<DataType>(vec, start_rank, mid_rank);
    Sort<DataType>(vec, mid_rank + 1, end_rank);
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};

}  // namespace sstl
