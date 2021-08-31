/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: bracket_match.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// output if match right
static bool BracketMatch(const Vector<char>& sentence) {
  Stack<char> bracket_stack;

  for (int i = 0; i < sentence.Size(); ++i) {
    if (sentence[i] == '(' || sentence[i] == '[' || sentence[i] == '{') {
      bracket_stack.Push(sentence[i]);
    } else if (sentence[i] == ')') {
      if (bracket_stack.Empty() || bracket_stack.Pop() != '(') {
        return false;
      }
    } else if (sentence[i] == ']') {
      if (bracket_stack.Empty() || bracket_stack.Pop() != '[') {
        return false;
      }
    } else if (sentence[i] == '}') {
      if (bracket_stack.Empty() || bracket_stack.Pop() != '{') {
        return false;
      }
    }
  }

  if (!bracket_stack.Empty()) {
    return false;
  }
  return true;
}
}  // namespace sstl
