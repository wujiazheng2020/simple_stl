/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_searcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/list.h"

namespace sstl {
// use in ordered list
// search in [p-n, p)
// time complexity O(n)
// no include p itself !
// if success return the listnode pointer
// if it is in disorderd, return nullptr
// if failure return the pointer whose data is no bigger than p->data !!
struct ListSearcher {
  template <typename DataType>
  static ListNode<DataType>* Search(const List<DataType>& list,
                                    const DataType& elem,
                                    const int& compare_times,
                                    ListNode<DataType>* search_start) {
    if (!list.CheckOrdered()) {
      return nullptr;
    }
    ListNode<DataType>* now_p = search_start->pred;
    for (int i = 0; i < compare_times; ++i) {
      if (now_p->data <= elem) {
        return now_p;
      } else {
        now_p = now_p->pred;
      }
    }
    return now_p;  // maybe the head;
  }

  template <typename DataType>
  static ListNode<DataType>* Search(const List<DataType>& list,
                                    const DataType& elem) {
    return Search<DataType>(list, elem, list.Size(), list.End());
  }
};
}  // namespace sstl
