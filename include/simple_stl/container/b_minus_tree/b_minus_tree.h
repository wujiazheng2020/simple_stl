/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: b_minus_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/searcher/left_right_mid_searcher.h"
#include "simple_stl/container/b_minus_tree/b_node.h"

namespace sstl {
// default (2,3) tree
template <typename DataType, int order = 3>
class BMinusTree {
 public:
  BMinusTree() : size_(0), order_(order), root_(new BNode<DataType>()) {}
  ~BMinusTree() {
    if (root_) {
      delete root_;
    }
  }

  const int& Size() const { return size_; }

  const int& Order() const { return order_; }

  bool Empty() const { return size_ == 0; }

  BNode<DataType>* Root() { return root_; }

  BNode<DataType>* Search(const DataType& elem) {
    BNode<DataType>* father_of_hit = nullptr;
    return Search(elem, &father_of_hit);
  }

  bool Insert(const DataType& elem) {
    BNode<DataType>* father_of_hit;
    BNode<DataType>* now_node = Search(elem, &father_of_hit);
    if (now_node) {
      return false;
    }

    now_node = father_of_hit;
    // no always O(n), usually O(1)
    now_node->key_vec->CheckOrdered();
    // locate
    int rank = LeftRightMidSearcher::Search(*now_node->key_vec, elem, true);
    now_node->key_vec->Insert(rank + 1, elem);
    now_node->child_vec->Insert(rank + 2, nullptr);
    ++size_;

    SolveOverFlow(now_node);
    return true;
  }

  bool Remove(const DataType& elem) {
    BNode<DataType>* now_node = Search(elem);
    if (!now_node) {
      return false;
    }

    // no always O(n), usually O(1)
    now_node->key_vec->CheckOrdered();
    int rank = LeftRightMidSearcher::Search(*now_node->key_vec, elem, true);
    // if not leaf, remove leftest deepest most leaf
    if (now_node->child_vec->Get(0)) {
      BNode<DataType>* succ_child = now_node->child_vec->Get(rank + 1);
      while (succ_child->child_vec->Get(0)) {
        succ_child = succ_child->child_vec->Get(0);
      }
      (*now_node->key_vec)[rank] = (*succ_child->key_vec)[0];
      now_node = succ_child;
      rank = 0;
    }
    now_node->key_vec->Remove(rank);
    now_node->child_vec->Remove(rank + 1);
    --size_;
    SolveUnderFlow(now_node);
    return true;
  }

 private:
  // if fail return nullptr;
  // if success return the match node
  BNode<DataType>* Search(const DataType& elem,
                          BNode<DataType>** father_of_hit) {
    BNode<DataType>* now_node = root_;
    *father_of_hit = nullptr;
    while (now_node) {
      // no always O(n), usually O(1)
      now_node->key_vec->CheckOrdered();
      // return the max rank which no bigger than elem
      int rank = LeftRightMidSearcher::Search(*now_node->key_vec, elem, true);
      if (rank >= 0 && now_node->key_vec->Get(rank) == elem) {
        return now_node;
      } else {
        *father_of_hit = now_node;
        now_node = now_node->child_vec->Get(rank + 1);
      }
    }
    return nullptr;
  }

  void SolveOverFlow(BNode<DataType>* now_node) {
    if (order_ >= now_node->child_vec->Size()) {
      return;
    }
    // select centre-left one as mid
    // example: key: 0 1 2 3 4 for (3,5) tree with (2,4) key
    //        child:0 1 2 3 4 5
    // mid : 4/2 = 2
    int rank_mid = (order_ - 1) / 2;
    BNode<DataType>* right_node = new BNode<DataType>();
    right_node->child_vec->PopBack();  // for the nullptr child
    for (int i = rank_mid + 1; i < order_; ++i) {
      right_node->key_vec->PushBack(now_node->key_vec->Get(i));
      right_node->child_vec->PushBack(now_node->child_vec->Get(i));
    }
    right_node->child_vec->PushBack(now_node->child_vec->Get(order_));
    now_node->key_vec->Remove(rank_mid + 1, order_);
    now_node->child_vec->Remove(rank_mid + 1, order_ + 1);

    // reset parent
    if (right_node->child_vec->Get(0)) {
      for (int i = 0; i < right_node->child_vec->Size(); ++i) {
        (*right_node->child_vec)[i]->parent = right_node;
      }
    }

    // deal with left node
    BNode<DataType>* now_father_node = now_node->parent;
    if (!now_father_node) {
      now_father_node = new BNode<DataType>();
      (*now_father_node->child_vec)[0] = now_node;
      now_node->parent = now_father_node;
      root_ = now_father_node;
    }

    now_node->key_vec->CheckOrdered();
    int no_big_rank = LeftRightMidSearcher::Search(
        *now_father_node->key_vec, now_node->key_vec->Get(0), true);
    int need_insert_rank = 1 + no_big_rank;
    // lift the node
    now_father_node->key_vec->Insert(need_insert_rank,
                                     now_node->key_vec->Get(rank_mid));
    now_node->key_vec->Remove(rank_mid);
    now_father_node->child_vec->Insert(need_insert_rank + 1, right_node);
    right_node->parent = now_father_node;
    SolveOverFlow(now_father_node);
  }

  void SolveUnderFlow(BNode<DataType>* now_node) {
    int under_flow_bound = (order_ + 1) / 2;
    if (under_flow_bound <= now_node->child_vec->Size()) {
      return;
    }
    BNode<DataType>* now_father_node = now_node->parent;
    // if it is root
    if (!now_father_node) {
      if (now_node->key_vec->Empty() && now_node->child_vec->Get(0)) {
        root_ = now_node->child_vec->Get(0);
        root_->parent = nullptr;
        now_node->child_vec->Put(0, nullptr);
        delete now_node;
      }
      // for empty node
      return;
    }

    // if it is not root
    // get rank in parent, it must exist
    int rank_in_parent = 0;
    while (now_node != now_father_node->child_vec->Get(rank_in_parent)) {
      ++rank_in_parent;
    }

    // 1. borrow from left brother
    if (rank_in_parent > 0) {  // make sure it have left brother
      BNode<DataType>* left_brother =
          now_father_node->child_vec->Get(rank_in_parent - 1);
      // left brother >= upper(m/2) + 1
      if (under_flow_bound < left_brother->child_vec->Size()) {
        now_node->key_vec->Insert(
            0, now_father_node->key_vec->Get(rank_in_parent - 1));
        now_father_node->key_vec->Put(rank_in_parent - 1,
                                      left_brother->key_vec->PopBack());
        now_node->child_vec->Insert(0, left_brother->child_vec->PopBack());
        if (now_node->child_vec->Get(0)) {
          (*now_node->child_vec)[0]->parent = now_node;
        }
        // this situation will not propagate to higher node
        return;
      }
    }

    // 2. borrow from right_brother
    if (rank_in_parent < now_father_node->child_vec->Size() -
                             1) {  // make sure it have right brother
      BNode<DataType>* right_brother =
          now_father_node->child_vec->Get(rank_in_parent + 1);
      // right brother >= upper(m/2) + 1
      if (under_flow_bound < right_brother->child_vec->Size()) {
        now_node->key_vec->PushBack(
            now_father_node->key_vec->Get(rank_in_parent));
        now_father_node->key_vec->Put(rank_in_parent,
                                      right_brother->key_vec->Get(0));
        right_brother->key_vec->Remove(0);
        now_node->child_vec->PushBack(right_brother->child_vec->Get(0));
        right_brother->child_vec->Remove(0);

        if (now_node->child_vec->Get(now_node->child_vec->Size() - 1)) {
          (*now_node->child_vec)[now_node->child_vec->Size() - 1]->parent =
              now_node;
        }
        // this situation will not propagate to higher node
        return;
      }
    }

    // 3. combined two
    // 3.1 combined with left_brother
    if (rank_in_parent > 0) {
      BNode<DataType>* left_brother =
          now_father_node->child_vec->Get(rank_in_parent - 1);
      // extract from parent
      left_brother->key_vec->PushBack(
          now_father_node->key_vec->Get(rank_in_parent - 1));
      now_father_node->key_vec->Remove(rank_in_parent - 1);
      // remove now_node which is right brother
      now_father_node->child_vec->Remove(rank_in_parent);

      left_brother->child_vec->PushBack(now_node->child_vec->Get(0));
      now_node->child_vec->Remove(0);

      // reset parent
      if (left_brother->child_vec->Get(left_brother->child_vec->Size() - 1)) {
        (*left_brother->child_vec)[left_brother->child_vec->Size() - 1]
            ->parent = left_brother;
      }

      for (int i = 0; i < now_node->key_vec->Size(); ++i) {
        left_brother->key_vec->PushBack(now_node->key_vec->Get(i));
        left_brother->child_vec->PushBack(now_node->child_vec->Get(i));
        if (left_brother->child_vec->Get(left_brother->child_vec->Size() - 1)) {
          (*left_brother->child_vec)[left_brother->child_vec->Size() - 1]
              ->parent = left_brother;
        }
      }
    } else {
      // 3.2 combined with right_brother
      BNode<DataType>* right_brother =
          now_father_node->child_vec->Get(rank_in_parent + 1);
      right_brother->key_vec->Insert(
          0, now_father_node->key_vec->Get(rank_in_parent));
      now_father_node->key_vec->Remove(rank_in_parent);
      // remove now_node which is the left brother
      now_father_node->child_vec->Remove(rank_in_parent);

      right_brother->child_vec->Insert(0, now_node->child_vec->PopBack());
      if (right_brother->child_vec->Get(0)) {
        (*right_brother->child_vec)[0]->parent = right_brother;
      }
      for (int i = now_node->key_vec->Size() - 1; i >= 0; --i) {
        right_brother->key_vec->Insert(0, now_node->key_vec->Get(i));
        right_brother->child_vec->Insert(0, now_node->child_vec->Get(i));
        if (right_brother->child_vec->Get(0)) {
          (*right_brother->child_vec)[0]->parent = right_brother;
        }
      }
    }
    delete now_node;

    SolveUnderFlow(now_father_node);
    return;
  }

 private:
  int size_;
  int order_;
  BNode<DataType>* root_;
};
}  // namespace sstl
