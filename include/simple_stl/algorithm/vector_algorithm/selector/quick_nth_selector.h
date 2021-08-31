/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: base_num_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
template <typename Partitioner>
struct QuickNthSelector {
  // time complexity O(n)
  // find k_th elem
  template <typename DataType>
  static DataType Select(const Vector<DataType>& vec, const int& start_rank,
                         const int& end_rank, const int& k_th) {
    int start = start_rank;
    int end = end_rank;
    Vector<DataType> vec2 = vec;
    while (start < end) {
      int mid_rank = Partitioner::Call(&vec2, start, end);
      if (mid_rank < start_rank + k_th) {
        start = mid_rank + 1;
      } else if (mid_rank > start_rank + k_th) {
        end = mid_rank;
      } else {
        return vec2.Get(mid_rank);
      }
    }
    return -1;
  }

  template <typename DataType>
  static DataType Select(const Vector<DataType>& vec, const int& k_th) {
    return Select<DataType>(vec, 0, vec.Size(), k_th);
  }
};
}  // namespace sstl
