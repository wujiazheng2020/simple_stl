/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_vector.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/vector_algorithm/finder/vector_finder.h"
#include "simple_stl/algorithm/vector_algorithm/traverser/vector_traverser.h"
#include "simple_stl/container/vector/vector.h"

TEST(TEST_VECTOR, TestVectorBasic) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(3);
  LOG(INFO) << vec.Size();
  EXPECT_EQ(vec.Size(), 2);

  LOG(INFO) << vec[0];
  vec.Put(1, 7);
  LOG(INFO) << vec.Get(1);
  EXPECT_EQ(vec[1], 7);

  EXPECT_EQ(vec.Insert(1, 22), 1);
  EXPECT_EQ(vec[1], 22);
  LOG(INFO) << vec.Get(1);

  EXPECT_EQ(vec.Remove(1), 1);
  LOG(INFO) << vec.Get(1);
  EXPECT_EQ(vec[1], 7);

  LOG(INFO) << "all:";
  sstl::VectorTraverser::Traverse(
      vec, [](const int& data) { LOG(INFO) << data; });
  LOG(INFO) << vec.CheckOrdered();
  EXPECT_EQ(vec.CheckOrdered(), 1);

  vec.Put(0, 9);
  LOG(INFO) << vec.CheckOrdered();
  EXPECT_EQ(vec.CheckOrdered(), 0);

  EXPECT_EQ(vec.PushBack(8), 3);
  LOG(INFO) << vec.Size();

  EXPECT_EQ(vec.Clear(), 3);
  EXPECT_EQ(vec.Size(), 0);
}

TEST(TEST_VECTOR, TestVectorAllocator) {
  sstl::Vector<int> vec;
  LOG(INFO) << vec.Size();
  LOG(INFO) << vec.Capcity();
  for (int i = 0; i < 1025; ++i) {
    vec.PushBack(i);
  }
  EXPECT_EQ(vec.Capcity(), 2048);

  LOG(INFO) << vec.Capcity();
  for (int i = 0; i < 999; ++i) {
    vec.PopBack();
  }

  const sstl::Vector<int> vec2 = vec;
  EXPECT_EQ(vec2.Tail(), 25);

  EXPECT_EQ(vec.Capcity(), 64);
  LOG(INFO) << vec.Capcity();
  LOG(INFO) << vec.Size();
  EXPECT_EQ(vec.Size(), 26);

  LOG(INFO) << "for linear";
  sstl::Vector<int, sstl::LinearAllocator<10>> vec_liner;

  LOG(INFO) << vec_liner.Size();
  LOG(INFO) << vec_liner.Capcity();
  for (int i = 0; i < 1025; ++i) {
    vec_liner.PushBack(i);
  }
  EXPECT_EQ(vec_liner.Capcity(), 1031);

  LOG(INFO) << vec_liner.Capcity();
  for (int i = 0; i < 999; ++i) {
    vec_liner.PopBack();
  }

  EXPECT_EQ(vec_liner.Capcity(), 101);
  LOG(INFO) << vec_liner.Capcity();
  LOG(INFO) << vec_liner.Size();
}

TEST(TEST_VECTOR, TestVectorCopy) {
  sstl::Vector<int> vec(10);
  LOG(INFO) << vec.Capcity();
  EXPECT_EQ(vec.Capcity(), 10);

  sstl::Vector<int> vec2(10, 11);
  EXPECT_EQ(vec2.Capcity(), 10 * 2);
  LOG(INFO) << vec2[8];
  EXPECT_EQ(vec2[8], 11);

  sstl::Vector<int> vec3(vec2, 0, 8);
  EXPECT_EQ(vec3.Capcity(), 8 * 2);
  LOG(INFO) << vec3[7];
  EXPECT_EQ(vec3[7], vec2[8]);

  sstl::Vector<int> vec4(vec2);
  LOG(INFO) << "size:" << vec4.Size();
  EXPECT_EQ(vec4.Size(), 10);
  EXPECT_EQ(vec4.Capcity(), 20);
  EXPECT_EQ(vec4[8], 11);

  sstl::Vector<int> vec5;
  vec5 = vec2;
  EXPECT_EQ(vec5.Size(), 10);
  EXPECT_EQ(vec5.Capcity(), 20);
  EXPECT_EQ(vec5[8], 11);
}
