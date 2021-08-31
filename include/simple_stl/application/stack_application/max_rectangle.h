/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: max_rectangle.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/pair/pair.h"
#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {

static int GetMaxRectangle(const Vector<int>& distribution) {
  if (distribution.Size() <= 0) {
    return -1;
  }
  Stack<Pair<int, int>> index_data_stack;
  index_data_stack.Push(MakePair(0, distribution[0]));
  int max_num = -1;
  for (int i = 1; i < distribution.Size(); ++i) {
    while (distribution[i] < index_data_stack.Top().second) {
      int square =
          (i - index_data_stack.Top().first) * index_data_stack.Top().second;
      if (square > max_num) {
        max_num = square;
      }
      index_data_stack.Pop();
    }
    if (distribution[i] > index_data_stack.Top().second) {
      index_data_stack.Push(MakePair(i, distribution[i]));
    }
  }
  return max_num;
}
}  // namespace sstl
