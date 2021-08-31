/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_deduplicator.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/list_algorithm/finder/list_finder.h"
#include "simple_stl/container/list/list.h"

namespace sstl {
// for disordered list
// time complexity O(n)
// return old_size - new_size;
struct ListDeDuplicator {
  template <typename DataType>
  static int Deduplicate(List<DataType>* list) {
    int old_size = list->Size();
    if (list->Size() > 1) {
      ListNode<DataType>* now_p = list->First();
      int ordered_size = 1;
      while (now_p->succ != list->End()) {
        now_p = now_p->succ;
        ListNode<DataType>* find_p =
            ListFinder::Find(now_p->data, ordered_size, now_p);
        if (find_p) {
          list->Remove(find_p);
        } else {
          ++ordered_size;
        }
      }
    }
    return old_size - list->Size();
  }
};
}  // namespace sstl
