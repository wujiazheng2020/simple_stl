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

#include "simple_stl/container/hash_map/open_hash_map.h"
#include "simple_stl/container/pair/pair.h"

namespace sstl {
// A. for simplification, we only support follow as key
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
template <typename Key, typename Value, int load_threshold = 3,
          template <typename Type> class BucketContainer = RedBlackTree>
class UnorderedMap {
 public:
  UnorderedMap()
      : load_threshold_(load_threshold),
        size_(0),
        capcity_(kInitCapcity),
        bucket_(new Vector<BucketContainer<Pair<Key, Value>>*>(
            kInitCapcity, new BucketContainer<Pair<Key, Value>>())) {}
  ~UnorderedMap() { delete bucket_; }

  const int& Size() const { return size_; }

  const int& Capcity() const { return capcity_; }

  bool Insert(const Pair<Key, Value>& entry) {
    Expand();
    int old_size = bucket_->Get(entry.first % capcity_)->Size();
    bucket_->Get(entry.first % capcity_)->Insert(entry);
    if (old_size < bucket_->Get(entry.first % capcity_)->Size()) {
      ++size_;
      return true;
    } else {
      return false;
    }
  }

  Pair<Key, Value>* Search(const Key& key) {
    auto node = bucket_->Get(key % capcity_)->Search(MakePair(key, Value()));
    if (node && node->data.first == key) {
      return &node->data;
    } else {
      return nullptr;
    }
  }

  bool Remove(const Key& key) {
    int old_size = bucket_->Get(key % capcity_)->Size();
    bucket_->Get(key % capcity_)->Remove(MakePair(key, Value()));
    if (old_size > bucket_->Get(key % capcity_)->Size()) {
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
      Vector<BucketContainer<Pair<Key, Value>>*>* new_bucket_ =
          new Vector<BucketContainer<Pair<Key, Value>>*>(
              new_capcity, new BucketContainer<Pair<Key, Value>>());
      for (int i = 0; i < capcity_; ++i) {
        InorderTraverserCommon::Visit(
            [=](const Pair<Key, Value>& entry) {
              new_bucket_->Get(entry.first % new_capcity)->Insert(entry);
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
  Vector<BucketContainer<Pair<Key, Value>>*>* bucket_;
};
}  // namespace sstl
