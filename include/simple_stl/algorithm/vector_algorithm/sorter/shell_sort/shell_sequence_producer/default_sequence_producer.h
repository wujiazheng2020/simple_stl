/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: default_sequence_producer.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
// you can use constexpr function to produce sequence in complie time
// seqence format = {-1, x, x, x, ...}
// -1 is for end condition
static const int default_sequence[10] = {-1, 1, 2, 4, 8, 16, 32, 64, 128, 256};

struct DefaultSequenceProducer {
  static int GetInitIndex(const int& total_size) {
    for (int i = 9; i >= 0; --i) {
      if (default_sequence[i] < total_size / 2) {
        return i;
      }
    }
    return -1;
  }

  static int GetSequenceNum(const int& now_index) {
    return default_sequence[now_index];
  }
};

}  // namespace sstl
