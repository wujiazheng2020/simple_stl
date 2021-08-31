/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: stack_permutation_check.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
// it is simulation
// left stack: [1,2,3 >
// right stack: < 1,2,3]
static bool JudgeStackPermutationValid(
    const Vector<char>& left_stack, const Vector<char>& right_stack) {
  int left_pointer = 0;
  int right_pointer = 0;

  Stack<char> mid_stack;
  while (right_pointer < right_stack.Size()) {
    mid_stack.Push(right_stack[right_pointer]);
    ++right_pointer;
    while (!mid_stack.Empty() && mid_stack.Top() == left_stack[left_pointer] &&
           left_pointer < left_stack.Size()) {
      ++left_pointer;
      mid_stack.Pop();
    }
  }
  return (mid_stack.Empty() && left_pointer >= left_stack.Size());
}
}  // namespace sstl
