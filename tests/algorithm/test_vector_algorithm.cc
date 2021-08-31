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

#include "simple_stl/container/vector/vector.h"

#include "simple_stl/algorithm/vector_algorithm/deduplicator/vector_deduplicator.h"
#include "simple_stl/algorithm/vector_algorithm/finder/vector_finder.h"
#include "simple_stl/algorithm/vector_algorithm/reverser/vector_reverser.h"
#include "simple_stl/algorithm/vector_algorithm/traverser/vector_traverser.h"
#include "simple_stl/algorithm/vector_algorithm/uniquifier/vector_uniquifier.h"

#include "simple_stl/algorithm/vector_algorithm/searcher/delay_judge_searcher.h"
#include "simple_stl/algorithm/vector_algorithm/searcher/fibonacci_searcher.h"
#include "simple_stl/algorithm/vector_algorithm/searcher/interpolation_searcher.h"
#include "simple_stl/algorithm/vector_algorithm/searcher/left_right_mid_searcher.h"
#include "simple_stl/algorithm/vector_algorithm/searcher/no_judege_searcher.h"

#include "simple_stl/algorithm/vector_algorithm/partition/parition_dup.h"
#include "simple_stl/algorithm/vector_algorithm/partition/parition_lgu.h"
#include "simple_stl/algorithm/vector_algorithm/partition/partition_lug.h"
#include "simple_stl/algorithm/vector_algorithm/selector/quick_nth_selector.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/interger_sort/base_num_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/interger_sort/count_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/qsort/vector_quick_sort_bad.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/qsort/vector_quick_sort_common.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/shell_sort/shell_sequence_producer/default_sequence_producer.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/shell_sort/shell_sequence_producer/pratt_sequence_producer.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/shell_sort/vector_shell_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_bubble_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_heap_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_insert_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_merge_sort.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_select_sort.h"

TEST(TEST_VECTOR_ALGORITHM, TestVectorDeduplicate) {
  sstl::Vector<int, sstl::DoubleTimesAllocator> vec;
  vec.PushBack(7);
  vec.PushBack(7);
  vec.PushBack(3);
  vec.PushBack(4);
  vec.PushBack(4);
  vec.PushBack(5);
  vec.PushBack(5);
  vec.PushBack(5);
  vec.PushBack(6);
  EXPECT_EQ(sstl::VectorFinder::Find(vec, 4), 3);
  EXPECT_EQ(sstl::VectorFinder::Find(vec, 9), -1);
  EXPECT_EQ(sstl::VectorUniquifier::Uniquify(&vec), -2);

  EXPECT_EQ(sstl::VectorDeduplicator::Deduplicate(&vec), 4);
  LOG(INFO) << "after deduplicate:";
  sstl::VectorTraverser::Traverse(vec,
                                  [](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_VECTOR_ALGORITHM, TestVectorUniquify) {
  sstl::Vector<int, sstl::DoubleTimesAllocator> vec;
  EXPECT_EQ(vec.Empty(), true);
  EXPECT_EQ(sstl::VectorUniquifier::Uniquify(&vec), 0);
  vec.PushBack(1);
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(2);
  vec.PushBack(2);
  vec.PushBack(5);
  vec.PushBack(5);
  vec.PushBack(5);
  vec.PushBack(6);
  EXPECT_EQ(vec.Tail(), 6);
  EXPECT_EQ(vec.CheckOrdered(), true);
  LOG(INFO) << sstl::VectorFinder::Find(vec, 4);
  LOG(INFO) << vec.CheckOrdered();
  LOG(INFO) << vec.CheckOrdered();

  EXPECT_EQ(sstl::VectorUniquifier::Uniquify(&vec), 5);
  LOG(INFO) << "after Uniquify:";
  sstl::VectorTraverser::Traverse(vec,
                                  [](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_VECTOR_ALGORITHM, TestVectorFinder) {
  LOG(INFO) << "finder_test:";
  sstl::Vector<int> vec;
  for (int i = 0; i < 100; i += 2) {
    vec.PushBack(i);
  }
  EXPECT_EQ(sstl::VectorFinder::Find(vec, 60), 30);
  EXPECT_EQ(sstl::VectorFinder::Find(vec, 59), -1);
}

TEST(TEST_VECTOR_ALGORITHM, TestVectorSeacher) {
  LOG(INFO) << "search_test";
  sstl::Vector<int> vec;
  for (int i = 0; i < 100; i += 2) {
    vec.PushBack(i);
  }
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 60, false), -2);
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 60, false), -2);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 60, false), -2);
  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 60, false), -2);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 60, false), -2);

  EXPECT_EQ(vec.CheckOrdered(), true);
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 60, false), 30);
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 59, true), 29);

  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 0, false), 0);
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 0, true), 0);
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, -1, true), -1);
  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 101, true), 49);

  EXPECT_EQ(sstl::LeftRightMidSearcher::Search(vec, 59, false), -1);

  // for delay judge
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 60, false), 30);
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 59, true), 29);

  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 0, false), 0);
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, -1, true), -1);
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 0, true), 0);
  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 101, true), 49);

  EXPECT_EQ(sstl::DelayJudgeSearcher::Search(vec, 59, false), -1);

  // for no judge
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 60, false), 30);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 59, true), 29);

  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 0, false), 0);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, -1, true), -1);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 0, true), 0);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 101, true), 49);

  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 59, false), -1);

  // for fibonacci
  const int fib1 = sstl::Fib<1>::value;
  const int fib3 = sstl::Fib<3>::value;
  const int fib20 = sstl::Fib<20>::value;
  EXPECT_EQ(fib1, 1);
  EXPECT_EQ(fib3, 2);
  EXPECT_EQ(fib20, 6765);

  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 60, false), 30);
  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 59, true), 29);

  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 0, false), 0);
  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, -1, true), -1);
  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 0, true), 0);
  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 101, true), 49);

  EXPECT_EQ(sstl::FibonacciSearcher::Search(vec, 59, false), -1);

  // for interpolation search
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 60, false), 30);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 59, true), 29);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 59, false), -1);

  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 0, false), 0);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, -1, true), -1);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 0, true), 0);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 500, true), 49);
  const sstl::Vector<int> vec7 = vec;
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec7, 60, true), 30);

  vec.PushBack(101);
  vec.PushBack(104);
  vec.PushBack(109);
  EXPECT_EQ(vec.CheckOrdered(), true);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 104, false), 51);
  EXPECT_EQ(sstl::InterpolationSearcher::Search(vec, 104, false), 51);

  vec.PushBack(1);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec, 22, false), -2);

  const sstl::Vector<int> vec8 = vec;
  EXPECT_EQ(vec7.CheckOrdered(), true);
  EXPECT_EQ(vec8.CheckOrdered(), false);
  EXPECT_EQ(sstl::NoJudgeSearcher::Search(vec8, 22, false), -2);
}

TEST(TEST_VECTOR_ALGORITHM, VectorSorter) {
  sstl::Vector<int> vec;
  vec.PushBack(7);
  vec.PushBack(4);
  vec.PushBack(6);
  vec.PushBack(4);
  vec.PushBack(5);
  vec.PushBack(6);
  vec.PushBack(3);
  vec.PushBack(2);
  vec.PushBack(1);
  vec.PushBack(10);
  vec.PushBack(11);

  LOG(INFO) << "bubble sort";
  sstl::Vector<int> vec2(vec);
  sstl::VectorBubbleSort::Sort(&vec2);
  sstl::VectorTraverser::Traverse(vec2,
                                  [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "O(1) sort";
  sstl::VectorBubbleSort::Sort(&vec2);
  sstl::VectorTraverser::Traverse(vec2,
                                  [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "insert sort";
  sstl::Vector<int> vec3(vec);
  sstl::VectorInsertSort::Sort(&vec3);
  sstl::VectorInsertSort::Sort(&vec3);
  sstl::VectorTraverser::Traverse(vec3,
                                  [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "select sort";
  sstl::Vector<int> vec4(vec);
  sstl::VectorSelectSort::Sort(&vec4);
  sstl::VectorSelectSort::Sort(&vec4);
  sstl::VectorTraverser::Traverse(vec4,
                                  [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "merge sort";
  sstl::Vector<int> vec5;
  vec5.PushBack(1);
  vec5.PushBack(3);
  vec5.PushBack(5);
  vec5.PushBack(12);
  vec5.PushBack(2);
  vec5.PushBack(4);
  vec5.PushBack(6);
  vec5.PushBack(8);

  sstl::VectorMergeSort::Sort(&vec5);
  sstl::VectorMergeSort::Sort(&vec5);
  sstl::VectorTraverser::Traverse(vec5,
                                  [](const int& data) { LOG(INFO) << data; });

  LOG(INFO) << "merge sort2";
  sstl::Vector<int> vec6(vec);
  sstl::VectorMergeSort::Sort(&vec6);
  EXPECT_EQ(vec6.Size(), vec.Size());
  sstl::VectorTraverser::Traverse(vec6,
                                  [](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_VECTOR_ALGORITHM, VectorReverse) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(3);
  vec.PushBack(4);
  vec.PushBack(5);
  vec.PushBack(6);

  sstl::VectorReverser::Reverse(&vec);

  sstl::VectorTraverser::Traverse(vec,
                                  [](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_VECTOR_ALGORITHM, CountSort) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(2);
  vec.PushBack(5);
  vec.PushBack(4);
  vec.PushBack(5);
  vec.PushBack(9);
  vec.PushBack(4);
  vec.PushBack(8);
  vec.PushBack(5);
  vec.PushBack(9);
  vec.PushBack(1);
  vec.PushBack(3);

  sstl::CountSort::Sort(&vec);

  sstl::VectorTraverser::Traverse(vec,
                                  [](const int& data) { LOG(INFO) << data; });
}

TEST(TEST_VECTOR_ALGORITHM, BaseNumSort) {
  sstl::Vector<int> vec;
  vec.PushBack(125);
  vec.PushBack(124);
  vec.PushBack(128);
  vec.PushBack(127);
  vec.PushBack(135);
  vec.PushBack(65464);
  vec.PushBack(123123);
  vec.PushBack(44554);
  vec.PushBack(89898);
  vec.PushBack(44464554);
  vec.PushBack(1231);
  vec.PushBack(12);

  sstl::BaseNumSort::Sort(&vec);

  sstl::VectorTraverser::Traverse(vec,
                                  [](const int& data) { LOG(INFO) << data; });
  sstl::BaseNumSort::Sort(&vec);
}

TEST(TEST_VECTOR_ALGORITHM, ShellSort) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(5);
  vec.PushBack(8);
  vec.PushBack(9);
  vec.PushBack(4);
  vec.PushBack(12);
  vec.PushBack(65);
  vec.PushBack(75);
  vec.PushBack(52);
  vec.PushBack(44);
  vec.PushBack(33);
  vec.PushBack(25);
  vec.PushBack(586);
  vec.PushBack(45);
  vec.PushBack(586);
  vec.PushBack(45);
  vec.PushBack(2);
  vec.PushBack(89);
  vec.PushBack(-1);

  std::cout << "default" << std::endl;
  sstl::Vector<int> vec2 = vec;
  sstl::VectorShellSort<sstl::DefaultSequenceProducer>::Sort(&vec2);

  sstl::VectorTraverser::Traverse(vec2,
                                  [](const int& data) { LOG(INFO) << data; });
  sstl::VectorShellSort<sstl::DefaultSequenceProducer>::Sort(&vec2);
  std::cout << "default:O(1)" << std::endl;
  sstl::VectorTraverser::Traverse(vec2,
                                  [](const int& data) { LOG(INFO) << data; });

  std::cout << "pratt" << std::endl;
  sstl::Vector<int> vec3 = vec;
  sstl::VectorShellSort<sstl::PrattSequenceProducer>::Sort(&vec3);

  sstl::VectorTraverser::Traverse(vec3,
                                  [](const int& data) { LOG(INFO) << data; });
  sstl::VectorShellSort<sstl::PrattSequenceProducer>::Sort(&vec3);
  std::cout << "Pratt:O(1)" << std::endl;
  sstl::VectorTraverser::Traverse(vec3,
                                  [](const int& data) { LOG(INFO) << data; });

  EXPECT_EQ(sstl::DefaultSequenceProducer::GetInitIndex(-23), -1);
  EXPECT_EQ(sstl::PrattSequenceProducer::GetInitIndex(-23), -1);
}

template <template <typename PartitionType> class Sorter, typename Partitioner>
struct TestAllSort {
  static void Sort() {
    sstl::Vector<int> vec;
    vec.PushBack(1);
    vec.PushBack(5);
    vec.PushBack(8);
    vec.PushBack(9);
    vec.PushBack(4);
    vec.PushBack(12);
    vec.PushBack(65);
    vec.PushBack(75);
    vec.PushBack(44);
    vec.PushBack(44);
    vec.PushBack(44);
    vec.PushBack(25);
    vec.PushBack(586);
    vec.PushBack(45);
    vec.PushBack(589);
    vec.PushBack(45);
    vec.PushBack(2);
    vec.PushBack(89);
    vec.PushBack(-1);

    sstl::Vector<int> vec21 = vec;
    Sorter<Partitioner>::Sort(&vec21);
    sstl::VectorTraverser::Traverse(
        vec21, [](const int& data) { std::cout << data << " ,"; });
    std::cout << std::endl;
    Sorter<Partitioner>::Sort(&vec21);
    EXPECT_EQ(vec21.CheckOrdered(), true);
    LOG(INFO) << "O(1) sort";
    sstl::VectorTraverser::Traverse(
        vec21, [](const int& data) { std::cout << data << " ,"; });
    std::cout << std::endl;
  }
};

TEST(TEST_VECTOR_ALGORITHM, QSort) {
  LOG(INFO) << "lug bad" << std::endl;
  TestAllSort<sstl::VectorQuickSortBad, sstl::PartitionLUG>::Sort();

  LOG(INFO) << "lug common" << std::endl;
  TestAllSort<sstl::VectorQuickSortCommon, sstl::PartitionLUG>::Sort();

  LOG(INFO) << "dup bad" << std::endl;
  TestAllSort<sstl::VectorQuickSortBad, sstl::PartitionDUP>::Sort();

  LOG(INFO) << "dup common" << std::endl;
  TestAllSort<sstl::VectorQuickSortCommon, sstl::PartitionDUP>::Sort();

  LOG(INFO) << "lgu bad" << std::endl;
  TestAllSort<sstl::VectorQuickSortBad, sstl::PartitionLGU>::Sort();

  LOG(INFO) << "lgu common" << std::endl;
  TestAllSort<sstl::VectorQuickSortCommon, sstl::PartitionLGU>::Sort();
}

TEST(TEST_VECTOR_ALGORITHM, QuickSelect) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(5);
  vec.PushBack(8);
  vec.PushBack(9);
  vec.PushBack(4);
  vec.PushBack(12);
  vec.PushBack(65);
  vec.PushBack(75);
  vec.PushBack(44);
  vec.PushBack(44);
  vec.PushBack(44);
  vec.PushBack(25);
  vec.PushBack(586);
  vec.PushBack(45);
  vec.PushBack(589);
  vec.PushBack(45);
  vec.PushBack(2);
  vec.PushBack(89);
  vec.PushBack(-1);

  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLGU>::Select(vec, -1), -1);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLGU>::Select(vec, 5), 8);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLGU>::Select(vec, vec.Size()-2), 586);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLGU>::Select(vec, vec.Size()+1), -1);

  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionDUP>::Select(vec, -1), -1);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionDUP>::Select(vec, 5), 8);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionDUP>::Select(vec, vec.Size()-2), 586);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionDUP>::Select(vec, vec.Size()+1), -1);

  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLUG>::Select(vec, -1), -1);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLUG>::Select(vec, 5), 8);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLUG>::Select(vec, vec.Size()-2), 586);
  EXPECT_EQ(sstl::QuickNthSelector<sstl::PartitionLUG>::Select(vec, vec.Size()+1), -1);
}

TEST(TEST_VECTOR_ALGORITHM, HeapSort) {
  sstl::Vector<int> vec;
  vec.PushBack(1);
  vec.PushBack(5);
  vec.PushBack(8);
  vec.PushBack(9);
  vec.PushBack(4);
  vec.PushBack(12);
  vec.PushBack(65);
  vec.PushBack(75);
  vec.PushBack(44);
  vec.PushBack(44);
  vec.PushBack(44);
  vec.PushBack(25);
  vec.PushBack(586);
  vec.PushBack(45);
  vec.PushBack(589);
  vec.PushBack(45);
  vec.PushBack(2);
  vec.PushBack(89);
  vec.PushBack(-1);

  LOG(INFO) << "heap sort";
  sstl::VectorHeapSort::Sort(&vec);
  sstl::VectorTraverser::Traverse(
      vec, [](const int& data) { std::cout << data << " ,"; });
  LOG(INFO) << "O(1) sort";
  sstl::VectorHeapSort::Sort(&vec);
  sstl::VectorTraverser::Traverse(
      vec, [](const int& data) { std::cout << data << " ,"; });
}