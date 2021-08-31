/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_insert_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/list.h"

namespace sstl {
struct ListInsertSort {
  template <typename DataType>
  static void Sort(List<DataType>* list, const int& n) {
    if (list->CheckOrdered()) {
      return;
    }
    ListNode<DataType>* start_p = list->First();
    ListNode<DataType>* head = start_p->pred;
    ListNode<DataType>* now_p = start_p;
    for (int i = 1; i < n; ++i) {
      now_p = now_p->succ;
      ListNode<DataType>* back_p = now_p;
      int j = i - 1;
      while (j >= 0) {
        back_p = back_p->pred;
        if (back_p->data <= now_p->data) {
          break;
        }
        --j;
      }

      ListNode<DataType>* tmp_p = now_p->succ;
      now_p->pred->succ = now_p->succ;
      now_p->succ->pred = now_p->pred;

      if (j < 0) {
        back_p = head;
      }
      now_p->succ = back_p->succ;
      back_p->succ->pred = now_p;
      back_p->succ = now_p;
      now_p->pred = back_p;
      now_p = tmp_p->pred;
    }
  }

  template <typename DataType>
  static void Sort(List<DataType>* list) {
    Sort<DataType>(list, list->Size());
  }
};
}  // namespace sstl
