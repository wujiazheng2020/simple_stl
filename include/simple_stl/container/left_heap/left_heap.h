/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: left_heap.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <limits>
#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/left_heap/left_heap_utils.h"

namespace sstl {
// big top heap
template <typename DataType>
class LeftHeap : public BinaryTree<DataType> {
 public:
  LeftHeap() {}
  virtual ~LeftHeap() {}

  // time complexity O(logn)
  void Insert(const DataType& data) {
    if (!this->Root()) {
      this->InsertAsRoot(data);
      return;
    }
    this->SetRoot(LeftHeapUtils::MergeTwoLeftHeap(
        this->Root(), new BinaryTreeNode<DataType>(data)));
    this->SetSize(this->Size() + 1);
  }

  const DataType& GetMax() const { return this->Root()->data; }

  // time complexity O(logn)
  DataType DeleteMax() {
    BinaryTreeNode<DataType>* left_heap = this->Root()->left_child;
    if (left_heap) {
      left_heap->parent = nullptr;
    }
    BinaryTreeNode<DataType>* right_heap = this->Root()->right_child;
    if (right_heap) {
      right_heap->parent = nullptr;
    }
    DataType elem = this->Root()->data;
    BinaryTreeNode<DataType>* old_root = this->Root();
    this->SetRoot(LeftHeapUtils::MergeTwoLeftHeap(left_heap, right_heap));
    delete old_root;
    this->SetSize(this->Size() - 1);
    return elem;
  }
};
}  // namespace sstl
