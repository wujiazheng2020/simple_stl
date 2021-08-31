/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list_node.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
template <typename DataType>
struct ListNode {
  ListNode() : pred(nullptr), succ(nullptr) {}
  explicit ListNode(const DataType& elem)
      : data(elem), pred(nullptr), succ(nullptr) {}
  ListNode(const DataType& elem, ListNode<DataType>* pred_p,
           ListNode<DataType>* succ_p)
      : data(elem), pred(pred_p), succ(succ_p) {}

  ListNode<DataType>* InsertAsPred(const DataType& elem) {
    ListNode<DataType>* new_elem = new ListNode<DataType>(elem, pred, this);
    if (pred) {
      pred->succ = new_elem;
    }
    pred = new_elem;
    return new_elem;
  }

  ListNode<DataType>* InsertAsSucc(const DataType& elem) {
    ListNode<DataType>* new_elem = new ListNode<DataType>(elem, this, succ);
    if (succ) {
      succ->pred = new_elem;
    }
    succ = new_elem;
    return new_elem;
  }

  template <typename VisitFunc>
  void TraverseAlongSucc(const VisitFunc& visit_fun) {
    ListNode<DataType>* now_p = this;
    visit_fun(now_p->data);
    while (now_p->succ) {
      now_p = now_p->succ;
      visit_fun(now_p->data);
    }
  }

  template <typename VisitFunc>
  void TraverseAlongPred(const VisitFunc& visit_fun) {
    ListNode<DataType>* now_p = this;
    visit_fun(now_p->data);
    while (now_p->pred) {
      now_p = now_p->pred;
      visit_fun(now_p->data);
    }
  }

  DataType data;
  ListNode<DataType>* pred;
  ListNode<DataType>* succ;
};
}  // namespace sstl
