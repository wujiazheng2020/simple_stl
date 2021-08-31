/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: huffman_char.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
template <typename ValueType>
struct HuffmanChar {
  HuffmanChar() {}
  HuffmanChar(const ValueType& the_value, const int& the_weight)
      : value(the_value), weight(the_weight), result_code(new Vector<char>()) {}
  ~HuffmanChar() {}

  bool operator<(const HuffmanChar& huffman_char) {
    return weight > huffman_char.weight;
  }

  bool operator==(const HuffmanChar& huffman_char) {
    return weight == huffman_char.weight;
  }

  ValueType value;
  int weight;
  Vector<char>* result_code;
};

template <typename ValueType>
static HuffmanChar<ValueType> MakeHuffmanChar(const ValueType& value,
                                              const int& weight) {
  HuffmanChar<ValueType> huffmanchar(value, weight);
  return huffmanchar;
}
}  // namespace sstl
