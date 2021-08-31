/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: postorder_traverser_bad.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree.h"

namespace sstl {
struct PostorderTraverserBad {
  // we use it for benchmark
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, BinaryTreeNode<NodeType>* node) {
    if (!node) return;
    Visit(visit_func, node->left_child);
    Visit(visit_func, node->right_child);
    visit_func(node->data);
  }
};
}  // namespace sstl
