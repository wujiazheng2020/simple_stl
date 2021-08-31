/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: majority_num_selector.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// majority_num is the number that appear more than half in a group
// maybe it doesn't exist
// here we assume it exist
struct MajorityNumSelector {
  // time complexity O(n)
  template <typename DataType>
  static DataType Select(const Vector<DataType>& vec, const int& start_rank,
                         const int& end_rank) {
    DataType maject_candidate;
    int repeat_times = 0;
    for (int i = start_rank, i < end_rank; ++i) {
      if (repeat_times == 0) {
        maject_candidate = vec[i];
        repeat_times = 1;
      } else {
        if (maject_candidate == vec[i]) {
          ++repeat_times;
        } else {
          --repeat_times;
        }
      }
    }
    return maject_candidate;
  }

  template <typename DataType>
  static DataType Select(const Vector<DataType>& vec) {
    Select<DataType>(vec, 0, vec.Size());
  }
};
}  // namespace sstl
