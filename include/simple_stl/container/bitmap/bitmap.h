/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: bitmap.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
class Bitmap {
 public:
  explicit Bitmap(const int& bit_size) {
    bype_size_ = (bit_size + 7) >> 3;
    memory_ = new char[bype_size_];
    for (int i = 0; i < bype_size_; ++i) {
      memory_[i] = 0;
    }
  }
  ~Bitmap() { delete[] memory_; }

  bool Test(const int& k_bit) const {
    // byte_index = k_bit>>3
    // bit_offset = k_bit&0x07    equals to k_bit%8
    // create mask 0x80 >> bit_offset
    if (k_bit > bype_size_ * 8 || k_bit < 0) {
      return false;
    }
    return memory_[k_bit >> 3] & (0x80 >> (k_bit & 0x07));
  }

  void Set(const int& k_bit) {
    Expand(k_bit);
    memory_[k_bit >> 3] |= (0x80 >> (k_bit & 0x07));
  }

  void Clear(const int& k_bit) {
    Expand(k_bit);
    memory_[k_bit >> 3] &= ~(0x80 >> (k_bit & 0x07));
  }

 private:
  void Expand(const int& k_bit) {
    if ((k_bit >> 3) >= bype_size_) {
      int new_byte_size = (k_bit + 7) >> 2;
      char* old_memeory = memory_;
      memory_ = new char[new_byte_size];
      for (int i = bype_size_; i < new_byte_size; ++i) {
        memory_[i] = 0;
      }
      for (int i = 0; i < bype_size_; ++i) {
        memory_[i] = old_memeory[i];
      }
      bype_size_ = new_byte_size;
      delete[] old_memeory;
    }
  }

  int bype_size_;
  char* memory_;
};
}  // namespace sstl
