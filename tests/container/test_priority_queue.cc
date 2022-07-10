/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_priority_queue.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <cmath>

#include "simple_stl/container/left_heap/left_heap.h"
#include "simple_stl/container/priority_queue/priority_queue.h"

template <typename PQueue>
void TestForAllCase(PQueue* p_queue) {
  for (int i = 0; i < 1000; ++i) {
    p_queue->Insert(floor(1e5 * sin(i)));
  }
  EXPECT_EQ(p_queue->Size(), 1000);

  int last_max = std::numeric_limits<int>::max();
  for (int i = 0; i < p_queue->Size(); ++i) {
    int new_max = p_queue->DeleteMax();
    EXPECT_LE(new_max, last_max);
    last_max = new_max;
  }
  delete p_queue;
}

TEST(TEST_PRIORITY_QUEUE, TEST_PRIORITY_QUEUE_ALL) {
  TestForAllCase(new sstl::PriorityQueue<int>());
  TestForAllCase(new sstl::PriorityQueue<int, sstl::CompleteHeap>());
  TestForAllCase(new sstl::PriorityQueue<int, sstl::LeftHeap>());
}
