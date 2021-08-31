/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: list.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/list/allocator/default_allocator.h"
#include "simple_stl/container/list/list_node.h"

namespace sstl {
template <typename DataType, typename Allocator = DefaultAllocator>
class List {
 public:
  List() { Init(); }
  List(const List<DataType>& other_list) {
    Init();
    CopyNodes(other_list);
  }
  ~List() { Clear(); }

  bool Empty() const { return size_ == 0 ? true : false; }

  const int& Size() const { return size_; }

  ListNode<DataType>* Begin() const { return header_; }

  ListNode<DataType>* End() const { return trailer_; }

  ListNode<DataType>* First() {
    is_ordered_ = false;
    if (header_->succ != trailer_) {
      return header_->succ;
    } else {
      return nullptr;
    }
  }

  const ListNode<DataType>* First() const {
    if (header_->succ != trailer_) {
      return header_->succ;
    } else {
      return nullptr;
    }
  }

  ListNode<DataType>* Last() {
    is_ordered_ = false;
    if (trailer_->pred != header_) {
      return trailer_->pred;
    } else {
      return nullptr;
    }
  }

  const ListNode<DataType>* Last() const {
    if (trailer_->pred != header_) {
      return trailer_->pred;
    } else {
      return nullptr;
    }
  }

  // return the new elem pointer
  ListNode<DataType>* InsertAsFirst(const DataType& elem) {
    ++size_;
    is_ordered_ = false;
    return header_->InsertAsSucc(elem);
  }

  // return the new elem pointer
  ListNode<DataType>* InsertAsLast(const DataType& elem) {
    ++size_;
    is_ordered_ = false;
    return trailer_->InsertAsPred(elem);
  }

  DataType Remove(ListNode<DataType>* p) {
    DataType elem = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --size_;
    return elem;
  }

  // real use api
  DataType RemoveFirst() { return Remove(header_->succ); }

  // real use api
  DataType RemoveLast() { return Remove(trailer_->pred); }

  bool CheckOrdered() {
    if (is_ordered_) {
      return true;
    } else {
      is_ordered_ = true;
      if (size_ > 1) {
        ListNode<DataType>* now_p = header_->succ;
        DataType last_data = now_p->data;
        while (now_p->succ != trailer_) {
          now_p = now_p->succ;
          if (last_data > now_p->data) {
            is_ordered_ = false;
            return false;
          }
          last_data = now_p->data;
        }
      }
      return true;
    }
  }

  const bool& CheckOrdered() const { return is_ordered_; }

  // for std stl
  int PushBack(const DataType& elem) {
    InsertAsLast(elem);
    return size_;
  }

  DataType PopBack() { return RemoveLast(); }

  int PushFront(const DataType& elem) {
    InsertAsFirst(elem);
    return size_;
  }

  DataType PopFront() { return RemoveFirst(); }

  DataType Tail() { return Last()->data; }

  const DataType& Tail() const { return trailer_->pred->data; }

  DataType Top() { return First()->data; }

  const DataType& Top() const { return header_->succ->data; }

  int Clear() {
    int old_size = size_;
    while (size_ > 0) {
      RemoveFirst();
    }
    return old_size;
  }

 private:
  void Init() {
    header_ = new ListNode<DataType>();
    trailer_ = new ListNode<DataType>();
    header_->succ = trailer_;
    trailer_->pred = header_;
    size_ = 0;
    is_ordered_ = true;
  }

  // i don't think copy from listnode is a good choice
  // so i chose to copy from the list directly
  void CopyNodes(const List<DataType>& other_list) {
    ListNode<DataType>* now_p = other_list.header_->succ;
    for (int i = 0; i < other_list.size_; ++i) {
      InsertAsLast(now_p->data);
      now_p = now_p->succ;
    }
    size_ = other_list.size_;
    is_ordered_ = other_list.is_ordered_;
  }

 private:
  bool is_ordered_;
  int size_;
  ListNode<DataType>* header_;
  ListNode<DataType>* trailer_;
};
}  // namespace sstl
