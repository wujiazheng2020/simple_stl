/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: postorder_traverser_common.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"

namespace sstl {
struct PostorderTraverserCommon {
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (node) {
      Stack<NodeType*> node_stack;
      node_stack.Push(node);
      NodeType* now_node = node;
      while (!node_stack.Empty()) {
        // if stack top is the right brother of now node
        if (node_stack.Top() != now_node->parent) {
          GotoLeftMost(&node_stack);
        }
        now_node = node_stack.Pop();
        visit_func(now_node->data);
      }
    }
  }

 private:
  template <typename NodeType>
  static void GotoLeftMost(Stack<NodeType*>* node_stack) {
    NodeType* now_node = node_stack->Top();
    while (now_node) {
      if (now_node->left_child) {
        if (now_node->right_child) {
          node_stack->Push(now_node->right_child);
        }
        node_stack->Push(now_node->left_child);
      } else if (now_node->right_child) {
        node_stack->Push(now_node->right_child);
      } else {
        // it is leaf
        break;
      }
      now_node = node_stack->Top();
    }
  }
};
}  // namespace sstl
