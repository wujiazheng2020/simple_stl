/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: level_traverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/queue/queue.h"

namespace sstl {
struct LevelTraverser {
  // it just like BFS
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    Queue<NodeType*> node_queue;
    node_queue.Enqueue(node);
    while (!node_queue.Empty()) {
      NodeType* now_node = node_queue.Dequeue();
      visit_func(now_node->data);
      if (now_node->left_child) {
        node_queue.Enqueue(now_node->left_child);
      }
      if (now_node->right_child) {
        node_queue.Enqueue(now_node->right_child);
      }
    }
  }
};
}  // namespace sstl
