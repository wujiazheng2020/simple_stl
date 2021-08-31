/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: auxililary_space.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"

namespace sstl {

template <typename DataType>
struct BinaryTreeNode {
  BinaryTreeNode<DataType>()
      : parent(nullptr), left_child(nullptr), right_child(nullptr), height(0) {}

  BinaryTreeNode<DataType>(const DataType& elem)
      : data(elem),
        parent(nullptr),
        left_child(nullptr),
        right_child(nullptr),
        height(0),
        color(kRedColor),
        null_path_length(1) {}

  BinaryTreeNode<DataType>(const DataType& elem,
                           BinaryTreeNode<DataType>* the_parent,
                           BinaryTreeNode<DataType>* the_left_child,
                           BinaryTreeNode<DataType>* the_right_child,
                           int the_height)
      : data(elem),
        parent(the_parent),
        left_child(the_left_child),
        right_child(the_right_child),
        height(the_height),
        color(kRedColor),
        null_path_length(1) {}

  // count all its child and itself
  // time complexity O(size)
  int Size() const {
    int total_size = 1;
    if (left_child) {
      total_size += left_child->Size();
    }
    if (right_child) {
      total_size += right_child->Size();
    }
    return total_size;
  }

  // get successor of this node of Inorder's Sequence
  // time complexity O(height)
  // it is useful
  BinaryTreeNode<DataType>* Succ() {
    BinaryTreeNode<DataType>* now_node = this;
    if (right_child) {
      now_node = right_child;
      while (now_node->left_child) {
        now_node = now_node->left_child;
      }
    } else {
      // just have left child or is just left
      while (BinaryTreeNodeUtils::IsRightChild(now_node)) {
        now_node = now_node->parent;
      }
      // maybe nullptr;
      now_node = now_node->parent;
    }
    return now_node;
  }

  BinaryTreeNode<DataType>* InsertAsLeftChild(const DataType& elem) {
    if (left_child) {
      return nullptr;
    } else {
      return (left_child = new BinaryTreeNode<DataType>(elem, this, nullptr,
                                                        nullptr, 0));
    }
  }

  BinaryTreeNode<DataType>* InsertAsRightChild(const DataType& elem) {
    if (right_child) {
      return nullptr;
    } else {
      return (right_child = new BinaryTreeNode<DataType>(elem, this, nullptr,
                                                         nullptr, 0));
    }
  }

  // basic part
  DataType data;
  BinaryTreeNode<DataType>* parent;
  BinaryTreeNode<DataType>* left_child;
  BinaryTreeNode<DataType>* right_child;

  // extend part
  int height;            // for all
  char color;            // 0 for red, 1 for black for red_black_tree
  int null_path_length;  // for left_heap
};
}  // namespace sstl
