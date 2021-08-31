/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: double_times_allocator.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {

struct DoubleTimesAllocator {
 public:
  template <typename DataType>
  static DataType* Malloc(DataType* old_elem, int* now_capcity) {
    int old_capcity = *now_capcity;
    DataType* new_elem = new DataType[(*now_capcity) <<= 1];
    for (int i = 0; i < old_capcity; ++i) {
      new_elem[i] = old_elem[i];
    }
    delete[] old_elem;
    return new_elem;
  }

  template <typename DataType>
  static DataType* ReleaseMemory(DataType* old_elem, int* now_capcity) {
    DataType* new_elem = new DataType[(*now_capcity) >>= 1];
    for (int i = 0; i < *now_capcity; ++i) {
      new_elem[i] = old_elem[i];
    }
    delete[] old_elem;
    return new_elem;
  }
};

}  // namespace sstl
