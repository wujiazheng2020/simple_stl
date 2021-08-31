/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: preorder_traverser_common.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"

namespace sstl {
struct PreorderTraverserCommon {
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (node) {
      Stack<NodeType*> node_stack;
      node_stack.Push(node);
      while (!node_stack.Empty()) {
        NodeType* now_node = node_stack.Pop();
        VisitAlongLeftLine(visit_func, now_node, &node_stack);
      }
    }
  }

 private:
  template <typename VisitFunc, typename NodeType>
  static void VisitAlongLeftLine(VisitFunc visit_func, NodeType* node,
                                 Stack<NodeType*>* node_stack) {
    NodeType* now_node = node;
    while (now_node) {
      visit_func(now_node->data);
      if (now_node->right_child) {
        node_stack->Push(now_node->right_child);
      }
      now_node = now_node->left_child;
    }
  }
};
}  // namespace sstl
