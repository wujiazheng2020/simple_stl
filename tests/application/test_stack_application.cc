/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_stack_application.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/vector_algorithm/traverser/vector_traverser.h"
#include "simple_stl/application/stack_application/bracket_match.h"
#include "simple_stl/application/stack_application/infix_calculator.h"
#include "simple_stl/application/stack_application/max_rectangle.h"
#include "simple_stl/application/stack_application/rpn_calculator.h"
#include "simple_stl/application/stack_application/stack_permutation_check.h"

TEST(STACK_APPLICATION, BracketMatch) {
  sstl::Vector<char> p;
  p.PushBack('(');
  p.PushBack('q');
  p.PushBack('[');
  p.PushBack('e');
  p.PushBack('q');
  p.PushBack(']');
  p.PushBack(')');
  EXPECT_EQ(sstl::BracketMatch(p), true);
  p.PushBack(')');
  EXPECT_EQ(sstl::BracketMatch(p), false);

  sstl::Vector<char> p2;
  p2.PushBack('(');
  p2.PushBack('(');
  p2.PushBack('(');
  p2.PushBack('(');
  p2.PushBack('(');
  EXPECT_EQ(sstl::BracketMatch(p2), false);

  sstl::Vector<char> p3;
  p3.PushBack('(');
  p3.PushBack('(');
  p3.PushBack(']');
  EXPECT_EQ(sstl::BracketMatch(p3), false);

  sstl::Vector<char> p4;
  p4.PushBack('(');
  p4.PushBack('(');
  p4.PushBack('}');
  EXPECT_EQ(sstl::BracketMatch(p4), false);
}

TEST(STACK_APPLICATION, InfixCalculate) {
  sstl::Vector<char> index_expression;
  index_expression.PushBack('(');
  index_expression.PushBack('0');
  index_expression.PushBack('!');
  index_expression.PushBack('+');
  index_expression.PushBack('1');
  index_expression.PushBack(')');
  index_expression.PushBack('*');
  index_expression.PushBack('2');
  index_expression.PushBack('^');
  index_expression.PushBack('(');
  index_expression.PushBack('3');
  index_expression.PushBack('!');
  index_expression.PushBack('+');
  index_expression.PushBack('4');
  index_expression.PushBack(')');
  index_expression.PushBack('-');
  index_expression.PushBack('(');
  index_expression.PushBack('5');
  index_expression.PushBack('!');
  index_expression.PushBack('-');
  index_expression.PushBack('6');
  index_expression.PushBack('7');
  index_expression.PushBack('-');
  index_expression.PushBack('(');
  index_expression.PushBack('8');
  index_expression.PushBack('+');
  index_expression.PushBack('9');
  index_expression.PushBack(')');
  index_expression.PushBack(')');
  index_expression.PushBack('/');
  index_expression.PushBack('4');
  index_expression.PushBack('E');

  EXPECT_EQ(sstl::InfixCalculator::Calculate(index_expression), 2039);

  sstl::Vector<char> index_expression2;
  index_expression2.PushBack(')');
  index_expression2.PushBack('0');
  index_expression2.PushBack('q');
  index_expression2.PushBack('1');
  EXPECT_EQ(sstl::InfixCalculator::Calculate(index_expression2), 0);

  sstl::Vector<char> rpn =
      sstl::InfixCalculator::GetRpnExpression(index_expression);
  sstl::VectorTraverser::Traverse(
      rpn, [](const char& data) { LOG(INFO) << data; });

  LOG(INFO) << "rpn2";
  sstl::Vector<char> rpn2 =
      sstl::InfixCalculator::GetRpnExpression(index_expression2);
  sstl::VectorTraverser::Traverse(
      rpn2, [](const char& data) { LOG(INFO) << data; });

  // rpn calculator don't consider the continus multiply
  EXPECT_EQ(sstl::RpnCalculator::Calculate(rpn), 124);
}

TEST(STACK_APPLICATION, RpnCalculation) {
  sstl::Vector<char> rpn_expression;
  rpn_expression.PushBack('0');
  rpn_expression.PushBack('!');
  rpn_expression.PushBack('1');
  rpn_expression.PushBack('+');
  rpn_expression.PushBack('2');
  rpn_expression.PushBack('3');
  rpn_expression.PushBack('^');
  rpn_expression.PushBack('4');
  rpn_expression.PushBack('!');
  rpn_expression.PushBack('-');
  rpn_expression.PushBack('5');
  rpn_expression.PushBack('!');
  rpn_expression.PushBack('6');
  rpn_expression.PushBack('/');
  rpn_expression.PushBack('-');
  rpn_expression.PushBack('7');
  rpn_expression.PushBack('*');
  rpn_expression.PushBack('8');
  rpn_expression.PushBack('*');
  rpn_expression.PushBack('-');
  rpn_expression.PushBack('9');
  rpn_expression.PushBack('-');
  rpn_expression.PushBack('9');
  rpn_expression.PushBack('+');
  rpn_expression.PushBack('6');
  rpn_expression.PushBack('+');

  EXPECT_EQ(sstl::RpnCalculator::Calculate(rpn_expression), 2024);
}

TEST(STACK_APPLICATION, StackPermutaion) {
  sstl::Vector<char> left_vec;
  left_vec.PushBack(5);
  left_vec.PushBack(4);
  left_vec.PushBack(3);
  left_vec.PushBack(2);
  left_vec.PushBack(1);
  sstl::Vector<char> right_vec;
  right_vec.PushBack(1);
  right_vec.PushBack(2);
  right_vec.PushBack(3);
  right_vec.PushBack(4);
  right_vec.PushBack(5);
  EXPECT_EQ(sstl::JudgeStackPermutationValid(left_vec, right_vec), true);

  sstl::Vector<char> l_vec2;
  sstl::Vector<char> r_vec2;

  // false when j+1  i  j   namely 312 sequence
  // i < j
  l_vec2.PushBack(5);  // 3
  l_vec2.PushBack(2);  // 1
  l_vec2.PushBack(3);  // 2
  l_vec2.PushBack(4);
  l_vec2.PushBack(1);

  r_vec2.PushBack(1);
  r_vec2.PushBack(2);
  r_vec2.PushBack(3);
  r_vec2.PushBack(4);
  r_vec2.PushBack(5);

  EXPECT_EQ(sstl::JudgeStackPermutationValid(l_vec2, r_vec2), false);
}

TEST(STACK_APPLICATION, MaxRectangle) {
  sstl::Vector<int> distribution;
  distribution.PushBack(1);
  distribution.PushBack(2);
  distribution.PushBack(4);
  distribution.PushBack(5);
  distribution.PushBack(3);
  distribution.PushBack(6);
  distribution.PushBack(8);
  distribution.PushBack(4);

  EXPECT_EQ(sstl::GetMaxRectangle(distribution), 12);
  sstl::Vector<int> distribution_empty;
  EXPECT_EQ(sstl::GetMaxRectangle(distribution_empty), -1);
}
