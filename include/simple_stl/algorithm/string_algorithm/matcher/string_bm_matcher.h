/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: string_bm_matcher.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/string/String.h"
#include "simple_stl/utility/utility.h"

namespace sstl {
struct StringBMMathcer {
  // return match index
  // time complexity: O(n + m) to O(n / m)
  // different from kmp, it match from P_end to P0
  static int Match(const String& P, const String& T) {
    Vector<int> bc_vec = BuildBC(P);
    Vector<int> gs_vec = BuildGoodSuffixVec(P);
    int T_index = 0;
    while (T_index <= T.Size() - P.Size()) {
      int end = P.Size() - 1;
      while (P[end] == T[T_index + end]) {
        --end;
        if (end < 0) {
          break;
        }
      }
      // success
      if (end < 0) {
        break;
      } else {
        T_index += Max(gs_vec[end], end - bc_vec[T[T_index + end]]);
      }
    }
    if (T_index > T.Size() - P.Size()) {
      return -1;
    } else {
      return T_index;
    }
  }

 private:
  // it means if unmatch in char A go to BC[A]
  static Vector<int> BuildBC(const String& P) {
    Vector<int> bc_vec(256, -1);
    for (int i = 0; i < P.Size(); ++i) {
      bc_vec[P[i]] = i;
      // painter algorithm , go to last same item first
    }
    return bc_vec;
  }

  // time complexity: O(m)
  // MaxMatchSequenceLength[j] = 5 means  P(j-5, j] = P[m-5,m)
  static Vector<int> BuildMaxMatchSequenceLengthVec(const String& P) {
    Vector<int> max_match_length_vec(P.Size(), 0);
    max_match_length_vec[P.Size() - 1] = P.Size();
    int start = P.Size() - 1;
    int end = start;
    int from_index = end - 1;
    while (from_index >= 0) {
      // 1. be covered
      if ((from_index > start) &&
          (max_match_length_vec[P.Size() - end + from_index - 1] <=
           from_index - start)) {
        max_match_length_vec[from_index] =
            max_match_length_vec[P.Size() - end + from_index - 1];
      } else {
        // 2. half no covered just compare the beyond part
        end = from_index;
        if (end < start) {
          start = end;
        }
        // 3. compare the beyaond part
        while ((start >= 0) && (P[start] == P[P.Size() - end + start - 1])) {
          --start;
        }
        max_match_length_vec[from_index] = end - start;
      }
      --from_index;
    }
    return max_match_length_vec;
  }

  static Vector<int> BuildGoodSuffixVec(const String& P) {
    Vector<int> max_match_vec = BuildMaxMatchSequenceLengthVec(P);
    Vector<int> good_suffix_vec(P.Size(), P.Size());
    int gs_index = 0;
    // 1. full match: P[0, from] = P[size - from -1, size)
    for (int from_index = P.Size() - 1; from_index >= 0; --from_index) {
      if (max_match_vec[from_index] == from_index + 1) {
        while (gs_index < P.Size() - from_index - 1) {
          good_suffix_vec[gs_index] = P.Size() - from_index - 1;
          ++gs_index;
        }
      }
    }
    // 2. part match: painter algorithm, for max length match
    for (int from_index = 0; from_index < P.Size() - 1; ++from_index) {
      good_suffix_vec[P.Size() - max_match_vec[from_index] - 1] =
          P.Size() - from_index - 1;
    }
    return good_suffix_vec;
  }
};
}  // namespace sstl
