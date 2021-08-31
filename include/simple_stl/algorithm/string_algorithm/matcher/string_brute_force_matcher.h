/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: string_brute_force_matcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/string/String.h"

namespace sstl {
struct StringBruteForceMathcer {
  // return match index
  // time complexity: O(n + m) to O(n*m)
  static int Match(const String& P, const String& T) {
    int T_index = 0;
    int P_index = 0;
    while (T_index < T.Size() && P_index < P.Size()) {
      if (T[T_index] == P[P_index]) {
        ++T_index;
        ++P_index;
      } else {
        T_index = T_index - P_index + 1;
        P_index = 0;
      }
    }
    if (P_index != P.Size()) {
      return -1;
    } else {
      return T_index - P_index;
    }
  }
};
}  // namespace sstl
