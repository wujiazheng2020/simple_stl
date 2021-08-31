/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: rpn_calculator.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

#include "simple_stl/application/stack_application/math_calculator.h"

namespace sstl {
class RpnCalculator {
 public:
  static int Calculate(const Vector<char>& rpn_expression) {
    Stack<int> num_stack;
    int index = 0;
    while (index < rpn_expression.Size()) {
      if (IsDigit(rpn_expression[index]) && index < rpn_expression.Size()) {
        num_stack.Push(rpn_expression[index] - '0');
      } else {
        if (rpn_expression[index] == '!') {
          num_stack.Push(MathCalulator::OneOperatorCalculate(
              rpn_expression[index], num_stack.Pop()));
        } else {
          int second = num_stack.Pop();
          int first = num_stack.Pop();
          num_stack.Push(MathCalulator::TwoOpertorCalculate(
              rpn_expression[index], first, second));
        }
      }
      ++index;
    }
    return num_stack.Top();
  }

 private:
  static bool IsDigit(const char& my_char) {
    return (my_char >= '0' && my_char <= '9');
  }
};

}  // namespace sstl
