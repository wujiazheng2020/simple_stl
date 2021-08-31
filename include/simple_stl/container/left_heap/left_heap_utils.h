/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: left_heap_utils.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"

namespace sstl {
struct LeftHeapUtils {
  template <typename NodeType>
  static NodeType* MergeTwoLeftHeap(NodeType* left_root, NodeType* right_root) {
    if (!left_root) {
      return right_root;
    }
    if (!right_root) {
      return left_root;
    }

    NodeType* left_node = left_root;
    NodeType* right_node = right_root;
    // swap
    if (left_root->data < right_root->data) {
      NodeType* tmp = left_node;
      left_node = right_node;
      right_node = tmp;
    }
    left_node->right_child =
        MergeTwoLeftHeap(left_node->right_child, right_node);
    left_node->right_child->parent = left_node;
    if (!left_node->left_child ||
        left_node->left_child->null_path_length <
            left_node->right_child->null_path_length) {
      NodeType* tmp = left_node->left_child;
      left_node->left_child = left_node->right_child;
      left_node->right_child = tmp;
    }
    if (left_node->right_child) {
      left_node->null_path_length =
          1 + left_node->right_child->null_path_length;
    } else {
      left_node->null_path_length = 1;
    }
    return left_node;
  }
};
}  // namespace sstl
