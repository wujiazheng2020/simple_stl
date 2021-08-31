/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: range_query_in_1d.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/avl_tree/avl_tree.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
template <typename DataType>
static Vector<DataType> RangeQueryIn1d(const AvlTree<DataType>& avl_tree,
                                       const DataType& start,
                                       const DataType& end) {
  Vector<DataType> data_vec;
  if (avl_tree.Empty()) {
    return data_vec;
  }
  BinaryTreeNode<DataType>* left_father;
  BinaryTreeNode<DataType>* left_node = avl_tree.Search(start, &left_father);

  if (!left_node) {
    left_node = left_father;
  }

  BinaryTreeNode<DataType>* right_father;
  BinaryTreeNode<DataType>* right_node = avl_tree.Search(end, &right_father);

  if (!right_node) {
    right_node = right_father;
  }

  if (left_node->data >= start) {
    data_vec.PushBack(left_node->data);
  }
  while (left_node != right_node) {
    left_node = left_node->Succ();
    data_vec.PushBack(left_node->data);
  }
  if (!data_vec.Empty() && data_vec.Tail() > end) {
    data_vec.PopBack();
  }
  return data_vec;
}
}  // namespace sstl
