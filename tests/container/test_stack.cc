/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_stack.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/container/list/allocator/default_allocator.h"
#include "simple_stl/container/list/list.h"
#include "simple_stl/container/stack/stack.h"
#include "simple_stl/container/vector/vector.h"

TEST(STACK_TEST, STACK_BASIC) {
  sstl::Stack<int> my_stack;
  EXPECT_EQ(my_stack.Empty(), true);

  my_stack.Push(5);
  my_stack.Push(6);
  my_stack.Push(5);
  my_stack.Push(4);
  my_stack.Push(3);
  my_stack.Push(2);
  my_stack.Push(1);

  EXPECT_EQ(my_stack.Size(), 7);
  EXPECT_EQ(my_stack.Top(), 1);
  EXPECT_EQ(my_stack.Top(), 1);
  EXPECT_EQ(my_stack.Pop(), 1);

  sstl::Stack<int, sstl::List> my_stack2;
  EXPECT_EQ(my_stack2.Empty(), true);

  my_stack2.Push(5);
  my_stack2.Push(6);

  EXPECT_EQ(my_stack2.Size(), 2);
  EXPECT_EQ(my_stack2.Top(), 6);
  EXPECT_EQ(my_stack2.Pop(), 6);
  my_stack2.Push(7);
  EXPECT_EQ(my_stack2.Clear(), 2);
  EXPECT_EQ(my_stack2.Size(), 0);

  const sstl::Stack<int> my_stack3 = my_stack;
  EXPECT_EQ(my_stack3.Top(), 2);

  EXPECT_EQ(my_stack.Clear(), 6);
  EXPECT_EQ(my_stack.Size(), 0);
}
