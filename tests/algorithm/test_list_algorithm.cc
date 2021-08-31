/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_list_algorithm.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "simple_stl/algorithm/list_algorithm/deduplicator/list_deduplicator.h"
#include "simple_stl/algorithm/list_algorithm/finder/list_finder.h"
#include "simple_stl/algorithm/list_algorithm/searcher/list_searcher.h"
#include "simple_stl/algorithm/list_algorithm/sorter/list_insert_sort.h"
#include "simple_stl/algorithm/list_algorithm/sorter/list_merge_sort.h"
#include "simple_stl/algorithm/list_algorithm/sorter/list_select_sort.h"
#include "simple_stl/algorithm/list_algorithm/traverser/list_traverser.h"
#include "simple_stl/algorithm/list_algorithm/uniquifier/list_uniquifier.h"
#include "simple_stl/container/list/list.h"

TEST(LIST_ALGORITHM, LIST_Duplicate) {
  sstl::List<int> my_list;
  EXPECT_EQ(sstl::ListDeDuplicator::Deduplicate(&my_list), 0);
  my_list.PushBack(1);
  my_list.PushBack(4);
  my_list.PushBack(4);
  my_list.PushBack(3);
  my_list.PushBack(4);
  my_list.PushBack(3);
  my_list.PushBack(5);
  my_list.PushBack(10);
  my_list.PushBack(2);
  my_list.PushBack(3);
  my_list.PushBack(4);
  my_list.PushBack(5);
  EXPECT_EQ(sstl::ListDeDuplicator::Deduplicate(&my_list), 6);
  EXPECT_EQ(sstl::ListUniquifier::Uniquify(&my_list), -1);
  LOG(INFO) << "after";
  sstl::ListTraverser::Traverse(
      my_list, [](const int& data) { LOG(INFO) << data; });
  EXPECT_EQ(my_list.CheckOrdered(), false);

  sstl::List<int> my_list2;
  EXPECT_EQ(my_list2.Size(), 0);
  EXPECT_EQ(sstl::ListUniquifier::Uniquify(&my_list2), 0);
  my_list2.PushBack(1);
  my_list2.PushBack(2);
  my_list2.PushBack(2);
  my_list2.PushBack(3);
  my_list2.PushBack(4);
  my_list2.PushBack(4);
  my_list2.PushBack(4);
  my_list2.PushBack(5);
  my_list2.PushBack(5);
  my_list2.PushBack(6);
  my_list2.PushBack(7);
  my_list2.PushBack(7);
  EXPECT_EQ(my_list2.Size(), 12);
  EXPECT_EQ(sstl::ListUniquifier::Uniquify(&my_list2), 5);

  LOG(INFO) << "unify:";
  sstl::ListTraverser::Traverse(
      my_list2, [](const int& data) { LOG(INFO) << data; });
  EXPECT_EQ(my_list2.Clear(), 7);
  EXPECT_EQ(my_list2.Size(), 0);
}

TEST(LIST_ALGORITHM, LIST_Seacher) {
  LOG(INFO) << "search test";
  sstl::List<int> my_list;
  my_list.InsertAsFirst(1);
  my_list.InsertAsFirst(2);
  my_list.InsertAsFirst(3);
  my_list.InsertAsFirst(4);
  my_list.InsertAsLast(8);
  my_list.InsertAsLast(9);
  my_list.InsertAsLast(11);

  EXPECT_EQ(sstl::ListFinder::Find(my_list, 7), nullptr);
  auto find_p = sstl::ListFinder::Find(my_list, 9);
  EXPECT_EQ(find_p->data, 9);
  auto find_p2 = sstl::ListFinder::Find(my_list, 4);
  EXPECT_EQ(find_p2->data, 4);
  auto find_p3 = sstl::ListFinder::Find(my_list, 11);
  EXPECT_EQ(find_p3->data, 11);
  EXPECT_EQ(my_list.CheckOrdered(), false);

  EXPECT_EQ(sstl::ListSearcher::Search(my_list, 8), nullptr);

  sstl::List<int> my_list2;
  EXPECT_EQ(my_list2.Empty(), true);
  my_list2.InsertAsFirst(10);
  my_list2.InsertAsFirst(9);
  my_list2.InsertAsFirst(8);
  my_list2.InsertAsFirst(7);
  my_list2.InsertAsFirst(6);
  my_list2.InsertAsFirst(5);
  my_list2.InsertAsFirst(3);
  my_list2.InsertAsFirst(1);

  EXPECT_EQ(my_list2.CheckOrdered(), true);
  EXPECT_EQ(my_list2.CheckOrdered(), true);

  auto my_node1 = sstl::ListSearcher::Search(my_list2, 7);
  EXPECT_EQ(my_node1->data, 7);
  auto my_node2 = sstl::ListSearcher::Search(my_list2, 5);
  EXPECT_EQ(my_node2->data, 5);
  auto my_node3 = sstl::ListSearcher::Search(my_list2, 10);
  EXPECT_EQ(my_node3->data, 10);
  auto my_node4 = sstl::ListSearcher::Search(my_list2, -1);
  EXPECT_EQ(my_node4->succ->data, 1);  // head

  auto my_node5 = sstl::ListSearcher::Search(my_list2, 4);
  EXPECT_EQ(my_node5->data, 3);

  auto my_node6 = sstl::ListSearcher::Search(my_list2, 11);
  EXPECT_EQ(my_node6->data, 10);

  const sstl::List<int> my_list3 = my_list2;
  EXPECT_EQ(my_list3.CheckOrdered(), true);
  auto my_node7 = sstl::ListSearcher::Search(my_list3, 5);
  EXPECT_EQ(my_node7->data, 5);
  auto my_node8 = sstl::ListFinder::Find(my_list3, 7);
  EXPECT_EQ(my_node8->data, 7);
  auto my_node9 = sstl::ListSearcher::Search(my_list3, -1);
  EXPECT_EQ(my_node9->succ->data, 1);
  auto my_node10 = sstl::ListFinder::Find(my_list3, 22);
  EXPECT_EQ(my_node10, nullptr);

  const sstl::List<int> my_list4 = my_list;
  EXPECT_EQ(sstl::ListSearcher::Search(my_list4, 5), nullptr);
}

TEST(LIST_ALGORITHM, LIST_SORT) {
  sstl::List<int> my_list;
  my_list.InsertAsFirst(3);
  my_list.InsertAsFirst(2);
  my_list.InsertAsFirst(5);
  my_list.InsertAsFirst(4);
  my_list.InsertAsFirst(7);
  my_list.InsertAsFirst(8);
  my_list.InsertAsFirst(1);
  my_list.InsertAsFirst(2);
  my_list.InsertAsFirst(3);
  my_list.InsertAsFirst(4);
  sstl::ListTraverser::Traverse(
      my_list, [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "select sort:";
  sstl::List<int> my_list2(my_list);
  sstl::ListSelectSort::Sort(&my_list2);
  sstl::ListSelectSort::Sort(&my_list2);
  sstl::ListTraverser::Traverse(
      my_list2, [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "insert sort:";
  sstl::List<int> my_list3(my_list);
  sstl::ListInsertSort::Sort(&my_list3);
  sstl::ListInsertSort::Sort(&my_list3);
  sstl::ListTraverser::Traverse(
      my_list3, [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "merge sort:";
  sstl::List<int> my_list4;
  my_list4.InsertAsFirst(8);
  my_list4.InsertAsFirst(2);
  my_list4.InsertAsFirst(4);
  my_list4.InsertAsFirst(7);
  my_list4.InsertAsFirst(5);
  my_list4.InsertAsFirst(1);
  my_list4.InsertAsFirst(3);
  my_list4.InsertAsFirst(3);
  my_list4.InsertAsFirst(10);
  sstl::ListMergeSort::Sort(&my_list4);
  sstl::ListMergeSort::Sort(&my_list4);
  sstl::ListTraverser::Traverse(
      my_list4, [](const int& data) { LOG(INFO) << data; });
}
