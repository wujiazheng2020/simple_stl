/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: interpolation_searcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// just like you looking up the book
// checkorderd first before use
// performance is based on vector distribution
// the equation is:
// (mi - start)/(end - start) =
// (search_elem - vec[start])/(vec[end-1] -vec[start])
// range from [start_rank, end_rank)
// average O(loglogn)
// worst O(n) !!
// if success return rank
// return the rank which elem[rank] is no bigger than search_elem (for insert)
struct InterpolationSearcher {
  template <typename DataType>
  static int Search(const Vector<DataType>& vec, const int& start_rank,
                    const int& end_rank, const DataType& search_elem,
                    bool for_insert) {
    if (!vec.CheckOrdered()) {
      return -2;
    }
    if (search_elem < vec[start_rank]) {
      return -1;
    }
    if (vec[end_rank - 1] < search_elem) {
      return end_rank - start_rank - 1;
    }

    int start = start_rank;
    int end = end_rank;
    int last_mid = -1;
    int mid = 0;
    while (last_mid != mid) {
      // this is expensive
      last_mid = mid;
      mid = start +
            (end - start) * (search_elem - vec[start]) /
                (vec[end - 1] - vec[start]);
      if (search_elem < vec[mid]) {
        end = mid;
      } else if (vec[mid] < search_elem) {
        start = mid + 1;
      } else {
        return mid;
      }
    }
    if (for_insert) {
      return mid - 1;
    } else {
      return -1;
    }
  }

  template <typename DataType>
  static int Search(const Vector<DataType>& vec, const DataType& search_elem,
                    bool for_insert) {
    return Search<DataType>(vec, 0, vec.Size(), search_elem, for_insert);
  }
};
}  // namespace sstl
