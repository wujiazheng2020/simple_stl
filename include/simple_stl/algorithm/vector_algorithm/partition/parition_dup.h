/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: partition_dup.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct PartitionDUP {
  // return the mid_rank
  // partition in [start, end)
  // deal with mass of duplicate element sort problem
  // in common situation it is worse than lug
  template <typename DataType>
  static int Call(Vector<DataType>* vec, const int& start_rank,
                  const int& end_rank) {
    int start = start_rank;
    int end = end_rank - 1;
    DataType pivot = vec->Get(start);
    while (start < end) {
      while (start < end) {
        if (pivot < vec->Get(end)) {
          --end;
        } else {
          // >=
          vec->Put(start, vec->Get(end));
          ++start;
          break;
        }
      }
      while (start < end) {
        if (pivot > vec->Get(start)) {
          ++start;
        } else {
          // <=
          vec->Put(end, vec->Get(start));
          --end;
          break;
        }
      }
    }
    vec->Put(start, pivot);
    return start;
  }
};
}  // namespace sstl
