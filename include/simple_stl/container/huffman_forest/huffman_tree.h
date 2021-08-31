/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: huffman_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/huffman_forest/huffman_char.h"

namespace sstl {
template <typename DataType>
class HuffmanTree : public BinaryTree<HuffmanChar<DataType>> {
 public:
  HuffmanTree() {}
  ~HuffmanTree() {}
};
}  // namespace sstl
