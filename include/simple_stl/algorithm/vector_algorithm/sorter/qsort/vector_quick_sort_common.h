/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_quick_sort_common.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/pair/pair.h"
#include "simple_stl/container/queue/queue.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// average: O(n^2) corresponding with the inverse pair
// but it is a unstable algorithm
template <typename Partitioner>
struct VectorQuickSortCommon {
  template <typename DataType>
  static void Sort(Vector<DataType>* vec, const int& start_rank,
                   const int& end_rank) {
    if (vec->CheckOrdered()) {
      return;
    }
    Queue<Pair<int, int>> rank_queue;
    rank_queue.Enqueue(MakePair(start_rank, end_rank));
    while (!rank_queue.Empty()) {
      Pair<int, int> range = rank_queue.Dequeue();
      int mid_rank = Partitioner::Call(vec, range.first, range.second);
      if (range.first < mid_rank) {
        rank_queue.Enqueue(MakePair(range.first, mid_rank));
      }
      if (mid_rank + 1 < range.second) {
        rank_queue.Enqueue(MakePair(mid_rank + 1, range.second));
      }
    }
  }

  template <typename DataType>
  static void Sort(Vector<DataType>* vec) {
    Sort<DataType>(vec, 0, vec->Size());
  }
};

}  // namespace sstl
