/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: avl_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree_utils.h"

namespace sstl {
template <typename DataType>
class AvlTree : public BinarySearchTree<DataType> {
 public:
  AvlTree() {}
  ~AvlTree() {}

  // time_complexity: O(logn)
  BinaryTreeNode<DataType>* Insert(const DataType& elem) override {
    BinaryTreeNode<DataType>* now_node =
        BinarySearchTree<DataType>::Insert(elem);
    BinaryTreeNode<DataType>* mid_node =
        RebalanceUtils::RebalanceToRoot(now_node);
    if (!mid_node->parent) {
      this->SetRoot(mid_node);
    }
    return now_node;
  }

  // time_complexity: O(logn)
  BinaryTreeNode<DataType>* Remove(const DataType& elem) override {
    BinaryTreeNode<DataType>* now_node =
        BinarySearchTree<DataType>::Remove(elem);
    BinaryTreeNode<DataType>* mid_node =
        RebalanceUtils::RebalanceToRoot(now_node);
    if (mid_node && !mid_node->parent) {
      this->SetRoot(mid_node);
    }
    return now_node;
  }
};
}  // namespace sstl
