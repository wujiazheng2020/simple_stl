/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_left_heap.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/container/left_heap/left_heap.h"

TEST(TEST_LEFT_HEAP, TEST_LEFT_HEAP_BASIC) {
  sstl::LeftHeap<int>* my_heap = new sstl::LeftHeap<int>();
  for (int i = 0; i < 1000; ++i) {
    my_heap->Insert(i);
    EXPECT_EQ(my_heap->GetMax(), i);
  }

  EXPECT_EQ(my_heap->Size(), 1000);
  EXPECT_EQ(my_heap->GetMax(), 999);

  int last_max = std::numeric_limits<int>::max();
  for (int i = 0; i < 1000; ++i) {
    int now_max = my_heap->DeleteMax();
    EXPECT_LE(now_max, last_max);
    last_max = now_max;
    LOG(INFO) << now_max;
  }
  EXPECT_EQ(my_heap->Size(), 0);
}
