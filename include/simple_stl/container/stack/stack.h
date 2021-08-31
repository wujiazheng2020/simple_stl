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

#include "simple_stl/container/vector/allocator/double_times_allocator.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// container can be vector or list
template <typename DataType,
          template <typename Type, typename Allocator> class Container = Vector,
          typename Allocator = DoubleTimesAllocator>
class Stack : protected Container<DataType, Allocator> {
 public:
  Stack() {}
  explicit Stack(const Container<DataType, Allocator>& other_stack)
      : Container<DataType, Allocator>(other_stack) {}
  ~Stack() {}

  bool Empty() const { return Container<DataType, Allocator>::Empty(); }

  const int& Size() const { return Container<DataType, Allocator>::Size(); }

  int Push(const DataType& elem) {
    return Container<DataType, Allocator>::PushBack(elem);
  }

  int Clear() { return Container<DataType, Allocator>::Clear(); }

  DataType Pop() { return Container<DataType, Allocator>::PopBack(); }

  DataType Top() { return Container<DataType, Allocator>::Tail(); }

  const DataType& Top() const { return Container<DataType, Allocator>::Tail(); }
};
}  // namespace sstl
