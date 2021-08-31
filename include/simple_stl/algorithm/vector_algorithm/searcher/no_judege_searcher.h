/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: no_judege_searcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// variants of binary search
// checkorderd first before use
// range from [start_rank, end_rank)
// average O(logn)
// best O(logn)
// if success return rank
// if is disordered return -2
// return the rank which elem[rank] is no bigger than search_elem (for insert)
struct NoJudgeSearcher {
  template <typename DataType>
  static int Search(const Vector<DataType>& vec, const int& start_rank,
                    const int& end_rank, const DataType& search_elem,
                    bool for_insert) {
    if (!vec.CheckOrdered()) {
      return -2;
    }
    int start = start_rank;
    int end = end_rank;
    while (start < end) {
      int mid = (start + end) >> 1;
      if (search_elem < vec[mid]) {
        end = mid;
      } else {
        start = mid + 1;
      }
    }
    if (for_insert) {
      return start - 1;
    } else {
      if (vec[start - 1] != search_elem) {
        return -1;
      } else {
        return start - 1;
      }
    }
  }

  template <typename DataType>
  static int Search(const Vector<DataType>& vec, const DataType& search_elem,
                    bool for_insert) {
    return Search<DataType>(vec, 0, vec.Size(), search_elem, for_insert);
  }
};
}  // namespace sstl
