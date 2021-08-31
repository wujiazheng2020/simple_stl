/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_list.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/list_algorithm/traverser/list_traverser.h"
#include "simple_stl/container/list/list.h"

TEST(TEST_LIST, TestListNode) {
  sstl::ListNode<int> list_empty;
  list_empty.InsertAsSucc(2);

  sstl::ListNode<int> list(544);
  auto head = list.InsertAsPred(6);
  list.InsertAsPred(10);
  list.InsertAsPred(11);
  list.InsertAsPred(12);
  auto tail = list.InsertAsSucc(22);
  list.InsertAsSucc(7);
  list.InsertAsSucc(8);

  LOG(INFO) << "from head";
  head->TraverseAlongSucc([](const int& data) { LOG(INFO) << data; });
  LOG(INFO) << "from tail";
  tail->TraverseAlongPred([](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_LIST, TestListBasic) {
  sstl::List<int> my_list;
  EXPECT_EQ(my_list.First(), nullptr);
  EXPECT_EQ(my_list.Last(), nullptr);

  my_list.InsertAsFirst(1);
  my_list.InsertAsFirst(2);
  my_list.InsertAsFirst(3);
  my_list.InsertAsFirst(4);
  my_list.InsertAsLast(8);
  my_list.InsertAsLast(9);
  my_list.InsertAsLast(11);
  LOG(INFO) << "size:" << my_list.Size();
  EXPECT_EQ(my_list.Size(), 7);

  sstl::ListTraverser::Traverse(
      my_list, [](const int& data) { LOG(INFO) << data; });

  EXPECT_EQ(my_list.First()->data, 4);
  EXPECT_EQ(my_list.Last()->data, 11);

  my_list.RemoveFirst();
  EXPECT_EQ(my_list.First()->data, 3);
  my_list.RemoveLast();
  EXPECT_EQ(my_list.Last()->data, 9);

  my_list.PushBack(5);
  EXPECT_EQ(my_list.Tail(), 5);
  EXPECT_EQ(my_list.PopBack(), 5);
  my_list.PushFront(5);
  EXPECT_EQ(my_list.Top(), 5);
  EXPECT_EQ(my_list.PopFront(), 5);
  my_list.PushBack(9);
  my_list.PushFront(10);

  const sstl::List<int> my_list2 = my_list;
  EXPECT_EQ(my_list2.Top(), 10);
  EXPECT_EQ(my_list2.Tail(), 9);
  EXPECT_EQ(my_list2.First()->data, 10);
  EXPECT_EQ(my_list2.Last()->data, 9);

  const sstl::List<int> my_list3;
  EXPECT_EQ(my_list3.First(), nullptr);
  EXPECT_EQ(my_list3.Last(), nullptr);
}
