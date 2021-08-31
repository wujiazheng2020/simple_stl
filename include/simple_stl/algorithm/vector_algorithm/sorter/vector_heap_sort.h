/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_heap_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>
#include "simple_stl/container/vector/vector.h"
#include "simple_stl/utility/utility.h"

namespace sstl {
// average: O(nlogn)
struct VectorHeapSort {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    MakeHeap(vec, start_rank, end_rank);
    for (int i = end_rank - 1; i >= start_rank + 1; --i) {
      Swap(&(*vec)[start_rank], &(*vec)[i]);
      PressDown(vec, start_rank, i - 1);
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }

 private:
  static int Parent(const int& now_index) { return (now_index - 1) >> 1; }

  static int LeftChild(const int& now_index) { return (now_index << 1) + 1; }

  static int RightChild(const int& now_index) { return (now_index << 1) + 2; }

  template <typename DataType>
  static void MakeHeap(Vector<DataType>* vec, const int& start_rank,
                       const int& end_rank) {
    int size = end_rank - start_rank;
    for (int i = size / 2 - 1 + start_rank; i >= start_rank; --i) {
      PressDown(vec, i, end_rank);
    }
  }

  template <typename DataType>
  static int PressDown(Vector<DataType>* vec, const int& index,
                       const int& end_rank) {
    int now_index = index;
    DataType now_data = vec->Get(now_index);
    while (true) {
      int left_son_index = LeftChild(now_index);
      int right_son_index = RightChild(now_index);
      DataType left_son_data = std::numeric_limits<int>::min();
      DataType right_son_data = std::numeric_limits<int>::min();
      if (right_son_index < end_rank) {
        left_son_data = vec->Get(left_son_index);
        right_son_data = vec->Get(right_son_index);
      } else if (left_son_index < end_rank) {
        left_son_data = vec->Get(left_son_index);
      } else {
        vec->Put(now_index, now_data);
        break;
      }
      if (now_data < left_son_data || now_data < right_son_data) {
        if (left_son_data < right_son_data) {
          vec->Put(now_index, right_son_data);
          now_index = right_son_index;
        } else {
          vec->Put(now_index, left_son_data);
          now_index = left_son_index;
        }
      } else {
        vec->Put(now_index, now_data);
        break;
      }
    }
    return now_index;
  }
};

}  // namespace sstl
