/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_traverser.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/list.h"

namespace sstl {
struct ListTraverser {
  template <typename DataType, typename VisitFunc>
  static void Traverse(const List<DataType>& list, const VisitFunc& visit_fun) {
    ListNode<DataType>* now_p = list.Begin();
    while (now_p->succ != list.End()) {
      now_p = now_p->succ;
      visit_fun(now_p->data);
    }
  }
};
}  // namespace sstl
