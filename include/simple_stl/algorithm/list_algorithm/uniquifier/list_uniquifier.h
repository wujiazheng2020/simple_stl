/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_uniquifier.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/list_algorithm/finder/list_finder.h"
#include "simple_stl/container/list/list.h"

namespace sstl {
// time complexity O(n)
// if is disordered return -1;
// return old_size - new_size;
struct ListUniquifier {
  template <typename DataType>
  static int Uniquify(List<DataType>* list) {
    if (!list->CheckOrdered()) {
      return -1;
    }
    if (list->Size() <= 1) {
      return 0;
    }

    int old_size = list->Size();
    ListNode<DataType>* now_p = list->First();
    DataType last_data = now_p->data;
    while (now_p->succ != list->End()) {
      now_p = now_p->succ;
      if (now_p->data == last_data) {
        ListNode<DataType>* delete_p = now_p;
        now_p = now_p->pred;
        list->Remove(delete_p);
      }
      last_data = now_p->data;
    }
    return old_size - list->Size();
  }
};
}  // namespace sstl
