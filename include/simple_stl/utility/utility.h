/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: utility.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
template <typename DataType>
static DataType Max(const DataType& a, const DataType& b) {
  return a < b ? b : a;
}

template <typename DataType>
static void Swap(DataType* left, DataType* right) {
  DataType tmp = *left;
  *left = *right;
  *right = tmp;
}

}  // namespace sstl
