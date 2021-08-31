/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector_traverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct VectorTraverser {
  template <typename DataType, typename VisitFunc>
  static void Traverse(const Vector<DataType>& vec, const VisitFunc& func) {
    for (int i = 0; i < vec.Size(); ++i) {
      func(vec[i]);
    }
  }
};
}  // namespace sstl
