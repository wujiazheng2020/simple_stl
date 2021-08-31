/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_select_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
struct ListSelectSort {
  template <typename DataType>
  static void Sort(List<DataType>* list, const int& n) {
    if (list->CheckOrdered()) {
      return;
    }
    ListNode<DataType>* start_p = list->First();
    ListNode<DataType>* head = start_p->pred;
    for (int i = n - 1; i >= 0; --i) {
      ListNode<DataType>* now_p = head->succ;
      ListNode<DataType>* max_p = head->succ;
      for (int j = 1; j <= i; ++j) {
        now_p = now_p->succ;
        if (max_p->data <= now_p->data) {
          max_p = now_p;
        }
      }

      now_p = now_p->succ;
      max_p->pred->succ = max_p->succ;
      max_p->succ->pred = max_p->pred;

      max_p->pred = now_p->pred;
      now_p->pred->succ = max_p;
      max_p->succ = now_p;
      now_p->pred = max_p;
    }
  }

  template <typename DataType>
  static void Sort(List<DataType>* list) {
    Sort<DataType>(list, list->Size());
  }
};

}  // namespace sstl
