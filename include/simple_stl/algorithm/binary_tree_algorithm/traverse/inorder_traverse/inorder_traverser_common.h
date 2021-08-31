/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: inorder_traverser_common.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"

namespace sstl {
struct InorderTraverserCommon {
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (node) {
      Stack<NodeType*> node_stack;
      NodeType* now_node = node;
      while (true) {
        PushAlongLeftLine(now_node, &node_stack);
        if (!node_stack.Empty()) {
          now_node = node_stack.Pop();
          visit_func(now_node->data);
          now_node = now_node->right_child;
        } else {
          break;
        }
      }
    }
  }

 private:
  template <typename NodeType>
  static void PushAlongLeftLine(NodeType* node, Stack<NodeType*>* node_stack) {
    NodeType* now_node = node;
    while (now_node) {
      node_stack->Push(now_node);
      now_node = now_node->left_child;
    }
  }
};
}  // namespace sstl
