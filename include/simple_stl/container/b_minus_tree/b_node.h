/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: b_node.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
template <typename DataType>
struct BNode {
  BNode() {
    parent = nullptr;
    key_vec = new Vector<DataType>();
    child_vec = new Vector<BNode<DataType>*>();
    child_vec->PushBack(nullptr);
  }

  BNode(const DataType& elem, BNode<DataType>* left_child,
        BNode<DataType>* right_child) {
    parent = nullptr;
    key_vec = new Vector<DataType>();
    child_vec = new Vector<BNode<DataType>*>();
    key_vec->PushBack(elem);
    child_vec->PushBack(left_child);
    child_vec->PushBack(right_child);
    if (left_child) {
      left_child->parent = this;
    }
    if (right_child) {
      right_child->parent = this;
    }
  }

  ~BNode() {
    if (key_vec) {
      delete key_vec;
    }
    if (child_vec) {
      delete child_vec;
    }
  }

  BNode<DataType>* parent;
  Vector<DataType>* key_vec;
  Vector<BNode<DataType>*>* child_vec;
};

}  // namespace sstl
