/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_merge_sort.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/list.h"

namespace sstl {
// we use iterator algorithm instead
// time complexity best O(nlogn)
// spatial complexity O(1)
struct ListMergeSort {
  template <typename DataType>
  static void Sort(List<DataType>* list, const int& n) {
    if (list->CheckOrdered()) {
      return;
    }
    ListNode<DataType>* start_p = list->First();
    ListNode<DataType>* head = start_p->pred;
    int internal = 2;
    while (internal < 2 * n) {
      ListNode<DataType>* now_p = head->succ;
      for (int i = 0; i < n; i += internal) {
        int k = i;
        ListNode<DataType>* start = now_p;
        ListNode<DataType>* mid = start;
        while (k < i + internal && k < n) {
          if (k == i + internal / 2) {
            mid = now_p;
          }
          now_p = now_p->succ;
          ++k;
        }
        Merge(start, mid, now_p);
        ListNode<DataType>* test = head;
        for (int a = 0; a < n; ++a) {
          test = test->succ;
        }
      }
      internal <<= 1;
    }
  }

  template <typename DataType>
  static void Sort(List<DataType>* list) {
    Sort<DataType>(list, list->Size());
  }

 private:
  // merge [start_p, mid_p) [mid_p, end_p)
  template <template <typename Type> class ListNode, typename DataType>
  static void Merge(ListNode<DataType>* start_p, ListNode<DataType>* mid_p,
                    ListNode<DataType>* end_p) {
    ListNode<DataType>* A_p = start_p;
    ListNode<DataType>* B_p = mid_p;
    while (A_p != mid_p && B_p != end_p) {
      if (A_p->data < B_p->data) {
        A_p = A_p->succ;
      } else {
        ListNode<DataType>* tmp = B_p->succ;
        // delete
        B_p->pred->succ = B_p->succ;
        B_p->succ->pred = B_p->pred;

        // insert
        B_p->pred = A_p->pred;
        B_p->succ = A_p;
        A_p->pred->succ = B_p;
        A_p->pred = B_p;
        B_p = tmp;
      }
    }
  }
};

}  // namespace sstl
