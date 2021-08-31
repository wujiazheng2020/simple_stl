/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: preorder_traverser_classic.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"

namespace sstl {
struct PreorderTraverserClassic {
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (node) {
      Stack<NodeType*> node_stack;
      node_stack.Push(node);
      while (!node_stack.Empty()) {
        NodeType* now_node = node_stack.Pop();
        visit_func(now_node->data);
        // right child first
        if (now_node->right_child) {
          node_stack.Push(now_node->right_child);
        }
        if (now_node->left_child) {
          node_stack.Push(now_node->left_child);
        }
      }
    }
  }
};
}  // namespace sstl
