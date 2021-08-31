/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_sring.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/string/String.h"

TEST(TEST_STRING, TEST_STRING_BASIC) {
  sstl::String my_string("fourier");
  EXPECT_EQ(my_string.Size(), 7);
  EXPECT_EQ(my_string.Prefix(4).Equal("four"), true);
  EXPECT_EQ(my_string.Prefix(5).Equal("four"), false);
  EXPECT_EQ(my_string.Prefix(5).Equal("fourz"), false);
  EXPECT_EQ(my_string.Prefix(5).Equal("fouri"), true);
  EXPECT_EQ(my_string.Prefix(5).Equal(my_string.Prefix(4)), false);
  EXPECT_EQ(my_string.Prefix(5).Equal(sstl::String("fourz")), false);
  EXPECT_EQ(my_string.Prefix(5).Equal(sstl::String("fouri")), true);
  EXPECT_EQ(my_string.Suffix(5).Equal("urier"), true);

  auto other_string = my_string.Prefix(5);
  other_string.Concat("OK");
  EXPECT_EQ(other_string.Equal("fouriOK"), true);
  other_string.Concat(sstl::String("Laplace"));
  EXPECT_EQ(other_string.Equal("fouriOKLaplace"), true);

  EXPECT_EQ(my_string.SubStr(3).Equal("rier"), true);
  EXPECT_EQ(my_string.SubStr(3,2).Equal("ri"), true);
}
