/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: priority_queue.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/complete_heap/complete_heap.h"

namespace sstl {
// big top heap
// container can be 1. left_heap or 2. complete heap
template <typename DataType,
          template <typename Type> class Container = CompleteHeap>
class PriorityQueue : public Container<DataType> {
 public:
  PriorityQueue() {}
  virtual ~PriorityQueue() {}

  // time complexity O(logn)
  void Insert(const DataType& data) { Container<DataType>::Insert(data); }

  const DataType& GetMax() const { return Container<DataType>::GetMax(); }

  // time complexity O(logn)
  DataType DeleteMax() { return Container<DataType>::DeleteMax(); }
};
}  // namespace sstl
