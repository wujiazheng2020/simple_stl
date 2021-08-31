/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: pratt_sequence_producer.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
// you can use constexpr function to produce sequence in complie time
// see fibonacci_searcher
// seqence format = {-1, x, x, x, ...}
// -1 is for end condition
static const int pratt_sequence[15] = {-1, 1,  2,  3,  4,  6,  8, 9,
                                       12, 16, 18, 24, 27, 32, 36};
struct PrattSequenceProducer {
  static int GetInitIndex(const int& total_size) {
    for (int i = 14; i >= 0; --i) {
      if (pratt_sequence[i] < total_size / 2) {
        return i;
      }
    }
    return -1;
  }

  static int GetSequenceNum(const int& now_index) {
    return pratt_sequence[now_index];
  }
};

}  // namespace sstl
