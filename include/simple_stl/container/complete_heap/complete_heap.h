/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: complete_heap.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// big top heap
template <typename DataType>
class CompleteHeap : public Vector<DataType> {
 public:
  CompleteHeap() {}
  ~CompleteHeap() {}

  typedef Vector<DataType> base;

  void operator=(const base& vec) {
    for (int i = 0; i < vec.Size(); ++i) {
      base::PushBack(vec[i]);
    }
  }

  // time complexity O(n)
  void MakeHeap() {
    for (int i = base::Size() / 2 - 1; i >= 0; --i) {
      PressDown(i);
    }
  }

  // time complexity O(logn)
  void Insert(const DataType& data) {
    base::PushBack(data);
    PopUp(base::Size() - 1);
  }

  const DataType& GetMax() const { return base::Get(0); }

  // time complexity O(logn)
  DataType DeleteMax() {
    DataType max_data = base::Get(0);
    base::Put(0, base::Tail());
    base::PopBack();
    PressDown(0);
    return max_data;
  }

 private:
  int Parent(const int& now_index) { return (now_index - 1) >> 1; }

  int LeftChild(const int& now_index) { return (now_index << 1) + 1; }

  int RightChild(const int& now_index) { return (now_index << 1) + 2; }

  // use for insert
  // pop the index-th node
  // return the final postion of the data
  int PopUp(const int& index) {
    int now_index = index;
    int now_data = base::Get(now_index);
    while (now_index >= 0) {
      int parent_index = Parent(now_index);
      if (parent_index < 0 || base::Get(parent_index) > now_data) {
        base::Put(now_index, now_data);
        break;
      }
      base::Put(now_index, base::Get(parent_index));
      now_index = parent_index;
    }
    return now_index;
  }

  // use for delete
  // press down the index-th node
  // return the final postion of the data
  int PressDown(const int& index) {
    int now_index = index;
    DataType now_data = base::Get(now_index);
    while (true) {
      int left_son_index = LeftChild(now_index);
      int right_son_index = RightChild(now_index);
      DataType left_son_data = std::numeric_limits<int>::min();
      DataType right_son_data = std::numeric_limits<int>::min();
      if (right_son_index < base::Size()) {
        left_son_data = base::Get(left_son_index);
        right_son_data = base::Get(right_son_index);
      } else if (left_son_index < base::Size()) {
        left_son_data = base::Get(left_son_index);
      } else {
        base::Put(now_index, now_data);
        break;
      }
      if (now_data < left_son_data || now_data < right_son_data) {
        if (left_son_data < right_son_data) {
          base::Put(now_index, right_son_data);
          now_index = right_son_index;
        } else {
          base::Put(now_index, left_son_data);
          now_index = left_son_index;
        }
      } else {
        base::Put(now_index, now_data);
        break;
      }
    }
    return now_index;
  }
};
}  // namespace sstl
