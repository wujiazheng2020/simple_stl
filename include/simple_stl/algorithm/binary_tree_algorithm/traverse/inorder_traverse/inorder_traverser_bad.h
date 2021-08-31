/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: inorder_traverser_bad.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
struct InorderTraverserBad {
  // we use it for benchmark
  template <typename VisitFunc, typename NodeType>
  static void Visit(VisitFunc visit_func, NodeType* node) {
    if (!node) return;
    Visit(visit_func, node->left_child);
    visit_func(node->data);
    Visit(visit_func, node->right_child);
  }
};
}  // namespace sstl
