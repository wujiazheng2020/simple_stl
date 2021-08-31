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

struct BaseNumSort {
  // notice: any support int
  // time complexity O(p*n)
  // p is the number of the max digits
  // sort in [start, end)
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    Vector<Vector<DataType>> bucket(16);
    int now_mask = 0x0F;
    int move_postion = 0;
    while (true) {
      // in bucket
      bool reach_max = true;
      for (int i = start_rank; i < end_rank; ++i) {
        int now_num = vec->Get(i) & now_mask;
        if (now_num) {
          reach_max = false;
        }
        int index = (now_num >> move_postion);
        bucket[index].PushBack(vec->Get(i));
      }
      if (reach_max) {
        return;
      }
      // off bucket
      int vec_index = start_rank;
      for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < bucket[i].Size(); ++j) {
          vec->Put(vec_index, bucket[i][j]);
          ++vec_index;
        }
        bucket[i].Clear();
      }
      now_mask <<= 4;
      move_postion += 4;
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};
}  // namespace sstl
