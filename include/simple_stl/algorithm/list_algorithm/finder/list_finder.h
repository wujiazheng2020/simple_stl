/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_finder.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/list.h"

namespace sstl {
// use in disordered list
// find in [p-n, p)
// time complexity O(n)
// no include p itself !
// if success return the listnode pointer
// if failure return nullptr
struct ListFinder {
  template <typename DataType>
  static ListNode<DataType>* Find(const DataType& elem,
                                  const int& compare_times,
                                  ListNode<DataType>* search_start) {
    ListNode<DataType>* now_p = search_start->pred;
    for (int i = 0; i < compare_times; ++i) {
      if (elem == now_p->data) {
        return now_p;
      } else {
        now_p = now_p->pred;
      }
    }
    return nullptr;
  }

  template <typename DataType>
  static ListNode<DataType>* Find(const List<DataType>& list,
                                  const DataType& search_elem) {
    return Find<DataType>(search_elem, list.Size(), list.End());
  }
};
}  // namespace sstl
