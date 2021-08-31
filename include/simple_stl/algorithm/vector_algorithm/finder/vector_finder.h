/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_finder.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// for disordered vector
// search in [start_rank, end_rank)
// success return rank
// if failture return start_rank - 1
struct VectorFinder {
  template <typename DataType>
  static int Find(const Vector<DataType>& vec, const int& start_rank,
                  const int& end_rank, const DataType& search_elem) {
    for (int i = start_rank; i < end_rank; ++i) {
      if (vec[i] == search_elem) {
        return i;
      }
    }
    return start_rank - 1;
  }

  template <typename DataType>
  static int Find(const Vector<DataType>& vec, const DataType& search_elem) {
    return Find<DataType>(vec, 0, vec.Size(), search_elem);
  }
};
}  // namespace sstl
