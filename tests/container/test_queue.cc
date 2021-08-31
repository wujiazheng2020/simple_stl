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

#include "simple_stl/container/queue/queue.h"

TEST(TEST_QUEUE, TestQueueBasic) {
  sstl::Queue<int> my_queue;
  EXPECT_EQ(my_queue.Empty(), true);

  my_queue.Enqueue(1);
  my_queue.Enqueue(2);
  my_queue.Enqueue(3);
  my_queue.Enqueue(4);
  my_queue.Enqueue(5);
  my_queue.Enqueue(6);
  EXPECT_EQ(my_queue.Top(), 1);
  EXPECT_EQ(my_queue.Dequeue(), 1);
  EXPECT_EQ(my_queue.Size(), 5);
  EXPECT_EQ(my_queue.Clear(), 5);
  EXPECT_EQ(my_queue.Size(), 0);
}
