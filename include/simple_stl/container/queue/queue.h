/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/allocator/default_allocator.h"
#include "simple_stl/container/list/list.h"

namespace sstl {
// prefer list, it is best container for queue
template <typename DataType, typename Allocator = DefaultAllocator>
class Queue : protected List<DataType, Allocator> {
 public:
  Queue() {}
  Queue(const Queue<DataType, Allocator>& other_queue)
      : List<DataType, Allocator>(other_queue) {}
  ~Queue() {}

  bool Empty() const { return List<DataType, Allocator>::Empty(); }

  const int& Size() const { return List<DataType, Allocator>::Size(); }

  int Clear() { return List<DataType, Allocator>::Clear(); }

  int Enqueue(const DataType& elem) {
    return List<DataType, Allocator>::PushBack(elem);
  }

  DataType Dequeue() { return List<DataType, Allocator>::PopFront(); }

  const DataType& Top() const { return List<DataType, Allocator>::Top(); }
};
}  // namespace sstl
