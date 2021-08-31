/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: dijkstra_end_function.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
struct DijkstraEndFunction {
  template <typename GraphMatrixType>
  static bool Call(GraphMatrixType* graph, const int& now_index,
                   const int& end_index) {
    return now_index == end_index ? true : false;
  }
};
}  // namespace sstl
