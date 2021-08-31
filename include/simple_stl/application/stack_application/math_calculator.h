/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: math_calculator.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
class MathCalulator {
 public:
  // support + - * / ^
  static int TwoOpertorCalculate(const char& operator_char, const int& num1,
                                 const int& num2) {
    switch (operator_char) {
      case '+':
        return num1 + num2;
      case '-':
        return num1 - num2;
      case '*':
        return num1 * num2;
      case '/':
        return num1 / num2;
      case '^':
        return Pow(num1, num2);
      default:
        return 0;
    }
  }

  // only support '!'
  static int OneOperatorCalculate(const char& operator_char, const int& num) {
    int result = 1;
    for (int i = 1; i <= num; ++i) {
      result *= i;
    }
    return result;
  }

  static int Pow(const int& a, const int& n) {
    int pow = 1;
    int rest_n = n;
    int p = a;
    while (rest_n > 0) {
      if (rest_n & 1) {
        pow *= p;
      }
      rest_n >>= 1;
      p *= p;
    }
    return pow;
  }
};

}  // namespace sstl
