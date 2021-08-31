/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: map.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/pair/pair.h"
#include "simple_stl/container/red_black_tree/red_black_tree.h"

namespace sstl {
// container can be
// 1. redblack_tree
// 2. splay_tree
// 3. avl_tree
// 4. binary_search_tree
template <typename Key, typename Value,
          template <typename Type> class Container = RedBlackTree>
class Map : public Container<Pair<Key, Value>> {
 public:
  Map() {}
  ~Map() {}

  BinaryTreeNode<Pair<Key, Value>>* Search(const Key& search_key) {
    return Container<Pair<Key, Value>>::Search(MakePair(search_key, Value()));
  }

  BinaryTreeNode<Pair<Key, Value>>* Remove(const Key& delte_key) {
    return Container<Pair<Key, Value>>::Remove(MakePair(delte_key, Value()));
  }
};
}  // namespace sstl
