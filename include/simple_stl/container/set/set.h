/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: set.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/red_black_tree/red_black_tree.h"

namespace sstl {
// container can be
// 1. redblack_tree
// 2. splay_tree
// 3. avl_tree
// 4. binary_search_tree
template <typename DataType,
          template <typename Type> class Container = RedBlackTree>
class Set : public Container<DataType> {
 public:
  Set() {}
  ~Set() {}
};
}  // namespace sstl
