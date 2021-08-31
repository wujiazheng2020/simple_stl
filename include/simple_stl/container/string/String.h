/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: open_hash_map.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/vector.h"

namespace sstl {
// this achievement is bad
// consider directly memory copy
class String : public Vector<char> {
 public:
  String() {}
  explicit String(const char* my_string) {
    int i = 0;
    while (my_string[i] != '\0') {
      Vector<char>::PushBack(my_string[i]);
      ++i;
    }
  }
  ~String() {}

  // return prefix with given length
  String Prefix(const int& length) const {
    String prefix;
    for (int i = 0; i < length; ++i) {
      prefix.PushBack(Get(i));
    }
    return prefix;
  }

  // return suffix with given length
  String Suffix(const int& length) const {
    String prefix;
    for (int i = Size() - length; i < Size(); ++i) {
      prefix.PushBack(Get(i));
    }
    return prefix;
  }

  String SubStr(const int& start, const int& length) const {
    String substr;
    for (int i = start; i < start + length; ++i) {
      substr.PushBack(Get(i));
    }
    return substr;
  }

  String SubStr(const int& start) const {
    String substr;
    for (int i = start; i < Size(); ++i) {
      substr.PushBack(Get(i));
    }
    return substr;
  }

  void Concat(const char* append_string) {
    int i = 0;
    while (append_string[i] != '\0') {
      PushBack(append_string[i]);
      ++i;
    }
  }

  void Concat(const String& other_string) {
    for (int i = 0; i < other_string.Size(); ++i) {
      PushBack(other_string[i]);
    }
  }

  bool Equal(const String& other_string) const {
    if (other_string.Size() != Size()) {
      return false;
    }
    for (int i = 0; i < other_string.Size(); ++i) {
      if (Get(i) != other_string[i]) {
        return false;
      }
    }
    return true;
  }

  bool Equal(const char* other_string) const {
    int i = 0;
    while (other_string[i] != '\0') {
      if (Get(i) != other_string[i]) {
        return false;
      }
      ++i;
    }
    if (i != Size()) {
      return false;
    }
    return true;
  }
};
}  // namespace sstl
