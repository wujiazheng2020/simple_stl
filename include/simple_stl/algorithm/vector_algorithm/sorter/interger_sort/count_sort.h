/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: count_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/bucket/interger_bucket.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct CountSort {
  // notice: any support num from 0 to 9
  // time complexity O(n)
  // sort in [start, end)
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    // you even don't need to check whether vec is in ordered
    IntergerBucket bucket;
    for (int i = start_rank; i < end_rank; ++i) {
      bucket.Set(vec->Get(i));
    }
    int vec_i = start_rank;
    for (int i = 0; i <= 9; ++i) {
      for (int j = 0; j < bucket.GetAcc(i); ++j) {
        vec->Put(vec_i, i);
        ++vec_i;
      }
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};
}  // namespace sstl
