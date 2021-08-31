/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: open_hash_map.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/container/red_black_tree/red_black_tree.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
constexpr const int kInitCapcity = 11;
// A. for simplification, we only support
//  1.char>0 , int8_t >0, uint_8
//  2.int>0 , int32_t>0, uint_32
//  3.short>0, int16_t>0, uint_16
//  4.long long>0, int64_t>0, uint_64
// B. container can be
//  1. redblack_tree
//  2. splay_tree
//  3. avl_tree
//  4. binary_search_tree
// load_threshold = 4 means , it will reload when capcity/size+1 < 4
// notice: this is unfinished class, just for study
template <typename DataType, int load_threshold = 3,
          template <typename Type> class BucketContainer = RedBlackTree>
class OpenHashMap {
 public:
  OpenHashMap()
      : load_threshold_(load_threshold),
        size_(0),
        capcity_(kInitCapcity),
        bucket_(new Vector<BucketContainer<DataType>*>(
            kInitCapcity, new BucketContainer<DataType>())) {}
  ~OpenHashMap() { delete bucket_; }

  const int& Size() const { return size_; }

  const int& Capcity() const { return capcity_; }

  bool Insert(const DataType& data) {
    Expand();
    int old_size = bucket_->Get(data % capcity_)->Size();
    bucket_->Get(data % capcity_)->Insert(data);
    if (old_size < bucket_->Get(data % capcity_)->Size()) {
      ++size_;
      return true;
    } else {
      return false;
    }
  }

  bool Search(const DataType& data) {
    auto node = bucket_->Get(data % capcity_)->Search(data);
    if (node && node->data == data) {
      return true;
    } else {
      return false;
    }
  }

  bool Remove(const DataType& data) {
    int old_size = bucket_->Get(data % capcity_)->Size();
    bucket_->Get(data % capcity_)->Remove(data);
    if (old_size > bucket_->Get(data % capcity_)->Size()) {
      --size_;
      return true;
    } else {
      return false;
    }
  }

 private:
  void Expand() {
    if (capcity_ / (size_ + 1) < load_threshold_) {
      int new_capcity = capcity_ * 4;
      Vector<BucketContainer<DataType>*>* new_bucket_ =
          new Vector<BucketContainer<DataType>*>(
              new_capcity, new BucketContainer<DataType>());
      for (int i = 0; i < capcity_; ++i) {
        InorderTraverserCommon::Visit(
            [=](const DataType& data) {
              new_bucket_->Get(data % new_capcity)->Insert(data);
            },
            bucket_->Get(i)->Root());
      }
      delete bucket_;
      bucket_ = new_bucket_;
      capcity_ = new_capcity;
    }
  }

 private:
  int load_threshold_;
  int size_;
  int capcity_;
  Vector<BucketContainer<DataType>*>* bucket_;
};

}  // namespace sstl
