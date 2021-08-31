/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: fibonacci_searcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <vector>
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// two way to count fib
// 1. directly, but the recursion deep is limited
template <int N>
struct Fib {
  constexpr static const int value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <>
struct Fib<2> {
  constexpr static const int value = 1;
};

template <>
struct Fib<1> {
  constexpr static const int value = 1;
};

// 2. just count_array
// N should > 2;
template <int N>
constexpr std::vector<int64_t> CalculateFibToNItem() {
  std::vector<int64_t> fib_vec(N);
  fib_vec[0] = 0;
  fib_vec[1] = 1;
  for (int32_t i = 2; i < N; ++i) {
    fib_vec[i] = fib_vec[i - 1] + fib_vec[i - 2];
  }
  return fib_vec;
}

// compute in compile time
static const std::vector<int64_t> fib_vec =
    sstl::CalculateFibToNItem<50>();
// variants of binary search
// checkorderd first before use
// change mi according to fib[n-1] -1
// range from [start_rank, end_rank)
// average O(1.440420logn) which is the best performation one in all binary
// seach
// best O(1)
// if success return rank
// return the rank which elem[rank] is no bigger than search_elem (for insert)
struct FibonacciSearcher {
  template <typename DataType>
  static int Search(const Vector<DataType>& vec, const int& start_rank,
                    const int& end_rank, const DataType& search_elem,
                    bool for_insert) {
    if (!vec.CheckOrdered()) {
      return -2;
    }
    int start = start_rank;
    int end = end_rank;
    int size = end - start;
    int now_fib_index = 0;
    // confirm item
    for (uint i = 0; i < fib_vec.size(); ++i) {
      if (size < fib_vec[i]) {
        now_fib_index = i - 1;
        break;
      }
    }

    while (now_fib_index > 0) {
      int mid = start + fib_vec[now_fib_index] - 1;
      if (search_elem < vec[mid]) {
        end = mid;
        --now_fib_index;
      } else if (vec[mid] < search_elem) {
        start = mid + 1;
        now_fib_index -= 2;
      } else {
        return mid;
      }
    }

    if (for_insert) {
      if (start > size) {
        start = size;
      }
      return start - 1;
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
