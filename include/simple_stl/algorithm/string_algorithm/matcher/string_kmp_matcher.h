/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: string_kmp_matcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/string/String.h"

namespace sstl {
struct StringKMPMathcer {
  // return match index
  // time complexity: O(n + m)
  static int Match(const String& P, const String& T) {
    Vector<int> next_vec = BuildNextVec(P);
    int P_index = 0;
    int T_index = 0;
    while (P_index < P.Size() && T_index < T.Size()) {
      if (P_index < 0 || T[T_index] == P[P_index]) {
        ++T_index;
        ++P_index;
      } else {
        P_index = next_vec[P_index];
      }
    }
    if (P_index < P.Size()) {
      return -1;
    } else {
      return T_index - P_index;
    }
  }

 private:
  // it means if in j unmatch go to next[j] re match
  // it still unmatch go to next[next[j]]
  // j > next[j]
  // so it will tend to -1 finally
  static Vector<int> BuildNextVec(const String& P) {
    Vector<int> next_vec(P.Size(), -1);
    int T_index = 0;
    int P_index = -1;
    while (T_index < P.Size() - 1) {
      if (P_index < 0 || P[T_index] == P[P_index]) {
        // if P[T_index] == P[P_index]
        // then if T_index+1 unmatch to P_index+1
        ++P_index;
        ++T_index;
        if (P[T_index] != P[P_index]) {
          next_vec[T_index] = P_index;
        } else {
          next_vec[T_index] = next_vec[P_index];
        }
      } else {
        P_index = next_vec[P_index];
      }
    }
    return next_vec;
  }
};
}  // namespace sstl
