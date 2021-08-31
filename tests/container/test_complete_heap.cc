/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_complete_heap.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "simple_stl/container/complete_heap/complete_heap.h"

TEST(TEST_COMPLETE_HEAP, TEST_HEAP_BASIC) {
  sstl::CompleteHeap<int> my_heap;
  for (int i = 0; i < 1000; ++i) {
    my_heap.Insert(i);
  }

  EXPECT_EQ(my_heap.Size(), 1000);
  EXPECT_EQ(my_heap.GetMax(), 999);

  for (int i = 0; i < my_heap.Size(); ++i) {
    int left_index = (i << 1) + 1;
    int right_index = (i << 1) + 2;
    if (left_index < my_heap.Size()) {
      EXPECT_LE(my_heap[left_index], my_heap[i]);
    }
    if (right_index < my_heap.Size()) {
      EXPECT_LE(my_heap[right_index], my_heap[i]);
    }
  }

  int last_max = std::numeric_limits<int>::max();
  for (int i = 0; i < my_heap.Size(); ++i) {
    int new_max = my_heap.DeleteMax();
    EXPECT_LE(new_max, last_max);
    last_max = new_max;
  }
}

TEST(TEST_COMPLETE_HEAP, TEST_HEAP_Construct) {
  sstl::CompleteHeap<int> my_heap;
  sstl::Vector<int> my_vector;

  for (int i = 0; i < 100; ++i) {
    my_vector.PushBack(floor(1e5 * sin(i)));
  }

  my_heap = my_vector;

  for (int i = 0; i < my_vector.Size(); ++i) {
    EXPECT_EQ(my_heap[i], my_vector[i]);
  }

  my_heap.MakeHeap();

  LOG(INFO) << "after_heap_make";
  for (int i = 0; i < my_heap.Size(); ++i) {
    int left_index = (i << 1) + 1;
    int right_index = (i << 1) + 2;
    if (left_index < my_heap.Size()) {
      EXPECT_LE(my_heap[left_index], my_heap[i]);
    }
    if (right_index < my_heap.Size()) {
      EXPECT_LE(my_heap[right_index], my_heap[i]);
    }
  }
}
