/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: infix_calculator.h
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
constexpr const char kOperatorNum = 9;
// should be load using io, but for simplification, ignore it
constexpr const char operator_prior[kOperatorNum][kOperatorNum] = {
  /* + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
  /* - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
  /* * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
  /* / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
  /* ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
  /* ! */ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
  /* ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
  /* ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
 /* \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '='
//         +    -    *    /    ^    !    (    )    \0
};

class InfixCalculator {
 public:
  static int Calculate(const Vector<char>& seq) {
    Stack<char> operator_stack;
    Stack<int> num_stack;
    operator_stack.Push('E');
    int now_index = 0;
    // for number
    while (!operator_stack.Empty() && now_index < seq.Size()) {
      int num = 0;
      bool has_digit = false;

      while (IsDigit(seq[now_index])) {
        num *= 10;
        num += (seq[now_index] - '0');
        ++now_index;
        has_digit = true;
      }
      if (has_digit) {
        num_stack.Push(num);
      }
      switch (operator_prior[CharToIndex(operator_stack.Top())]
                            [CharToIndex(seq[now_index])]) {
        case '<':
          operator_stack.Push(seq[now_index]);
          ++now_index;
          break;
        case '>':
          if (operator_stack.Top() == '!') {
            num_stack.Push(MathCalulator::OneOperatorCalculate(
                operator_stack.Top(), num_stack.Pop()));
          } else {
            num_stack.Push(MathCalulator::TwoOpertorCalculate(
                operator_stack.Top(), num_stack.Pop(), num_stack.Pop()));
          }
          operator_stack.Pop();
          // don't ++now_index
          break;
        case '=':
          operator_stack.Pop();
          ++now_index;
          break;
        default:
          ++now_index;
          break;
      }
    }
    return num_stack.Top();
  }

  static Vector<char> GetRpnExpression(const Vector<char>& seq) {
    Stack<char> operator_stack;
    Stack<int> num_stack;
    Vector<char> rpn_expression;
    operator_stack.Push('E');
    int now_index = 0;
    // for number
    while (!operator_stack.Empty() && now_index < seq.Size()) {
      int num = 0;
      bool has_digit = false;

      while (IsDigit(seq[now_index])) {
        num *= 10;
        num += (seq[now_index] - '0');
        rpn_expression.PushBack(seq[now_index]);
        ++now_index;
        has_digit = true;
      }
      if (has_digit) {
        num_stack.Push(num);
      }
      switch (operator_prior[CharToIndex(operator_stack.Top())]
                            [CharToIndex(seq[now_index])]) {
        case '<':
          operator_stack.Push(seq[now_index]);
          ++now_index;
          break;
        case '>':
          if (operator_stack.Top() == '!') {
            rpn_expression.PushBack('!');
          } else {
            rpn_expression.PushBack(operator_stack.Top());
            num_stack.Pop();
          }
          operator_stack.Pop();
          // don't ++now_index
          break;
        case '=':
          operator_stack.Pop();
          ++now_index;
          break;
        default:
          ++now_index;
          break;
      }
    }
    return rpn_expression;
  }

 private:
  static bool IsDigit(const char& my_char) {
    return (my_char >= '0' && my_char <= '9');
  }

  static int CharToIndex(const char& my_char) {
    switch (my_char) {
      case '+':
        return 0;
      case '-':
        return 1;
      case '*':
        return 2;
      case '/':
        return 3;
      case '^':
        return 4;
      case '!':
        return 5;
      case '(':
        return 6;
      case ')':
        return 7;
      case 'E':
        return 8;
      default:
        return 0;
    }
  }
};
}  //  namespace sstl
