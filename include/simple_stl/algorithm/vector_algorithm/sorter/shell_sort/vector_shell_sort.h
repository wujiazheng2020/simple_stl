/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_shell_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2)
template <typename SequenceProducer>
struct VectorShellSort {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    int now_index = SequenceProducer::GetInitIndex(vec->Size());
    while (now_index > 0) {
      int interval = SequenceProducer::GetSequenceNum(now_index);
      // here we must use a inverse pair related algorithm like insert sort
      for (int i = start_rank + interval; i < end_rank; i += interval) {
        DataType now_elem = (*vec)[i];
        int j = i - interval;
        while (j >= start_rank) {
          // for stable
          if ((*vec)[j] < now_elem || (*vec)[j] == now_elem) {
            (*vec)[j + interval] = now_elem;
            break;
          }
          (*vec)[j + interval] = (*vec)[j];
          j -= interval;
        }
        if (j == start_rank - interval) {
          (*vec)[start_rank] = now_elem;
        }
      }
      --now_index;
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};
}  // namespace sstl
