/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_merge_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/auxiliary_space/auxiliary_space.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {

// we use class here
// average time complexity:O(nlogn)
// spatial complexity:O(n)
class VectorMergeSort {
 public:
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    int size = end_rank - start_rank;
    AuxiliarySpace<DataType>* auxiliary_space =
        new AuxiliarySpace<DataType>(size + 1);

    int interval = 2;
    while (interval < (end_rank - start_rank) * 2) {
      int start_i = start_rank;
      while (start_i < end_rank) {
        int end_i = start_i + interval;
        int mid = (start_i + end_i) >> 1;
        if (mid > end_rank) {
          mid = end_rank;
        }
        if (end_i > end_rank) {
          end_i = end_rank;
        }
        Merge(vec, start_i, mid, end_i, auxiliary_space);
        start_i += interval;
      }
      interval <<= 1;
    }

    delete auxiliary_space;
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }

 private:
  // merge [start, mid) and [mid, end)
  template <typename DataType>
  static void Merge(Vector<DataType>* vec, const int& start, const int& mid,
                    const int& end, AuxiliarySpace<DataType>* auxiliary_space) {
    for (int i = start; i < mid; ++i) {
      auxiliary_space->Elem()[i - start] = (*vec)[i];
    }
    int A_size = mid - start;
    auxiliary_space->SetSize(A_size);

    int A_start = 0;
    int A_end = A_size;
    int B_start = mid;
    int B_end = end;
    int total_index = start;
    while (A_start < A_end) {
      // for stable
      if (B_start >= B_end ||
          auxiliary_space->Elem()[A_start] <= (*vec)[B_start]) {
        (*vec)[total_index] = auxiliary_space->Elem()[A_start];
        ++A_start;
      } else {
        (*vec)[total_index] = (*vec)[B_start];
        ++B_start;
      }
      ++total_index;
    }
  }
};
}  // namespace sstl
