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

namespace sstl {
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
class UnorderedSet
    : public OpenHashMap<DataType, load_threshold, BucketContainer> {
 public:
  UnorderedSet() {}
  ~UnorderedSet() {}
};
}  // namespace sstl
