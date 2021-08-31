/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_vector_algorithm.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/string_algorithm/matcher/string_brute_force_matcher.h"
#include "simple_stl/algorithm/string_algorithm/matcher/string_kmp_matcher.h"
#include "simple_stl/algorithm/string_algorithm/matcher/string_bm_matcher.h"
#include "simple_stl/container/string/String.h"

template <typename Matcher>
void TestForALL() {
  sstl::String T_string("asdsdakadababababdasdw");

  sstl::String P_string1("ababa");
  EXPECT_EQ(Matcher::Match(P_string1, T_string), 9);

  sstl::String P_string2("bababda");
  EXPECT_EQ(Matcher::Match(P_string2, T_string), 12);

  sstl::String P_string3("dwa");
  EXPECT_EQ(Matcher::Match(P_string3, T_string), -1);

  sstl::String P_string4("casd");
  EXPECT_EQ(Matcher::Match(P_string4, T_string), -1);
}

TEST(TEST_STRING_ALGORITHM, TEST_STRING_MATCH) {
  TestForALL<sstl::StringBruteForceMathcer>();
  TestForALL<sstl::StringKMPMathcer>();
  TestForALL<sstl::StringBMMathcer>();
}
