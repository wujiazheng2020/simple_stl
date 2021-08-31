/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: preorder_traverser_bad.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
struct PreorderTraverserBad {
  // we use it for benchmark
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (!node) return;
    visit_func(node->data);
    Visit(visit_func, node->left_child);
    Visit(visit_func, node->right_child);
  }
};
}  // namespace sstl
