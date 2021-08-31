/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: test_huffman_tree.cc
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <vector>
#include "simple_stl/algorithm/binary_tree_algorithm/traverse/level_traverse/level_traverser.h"
#include "simple_stl/container/huffman_forest/huffman_forest.h"
#include "simple_stl/container/vector/vector.h"

TEST(TEST_HUFFMAN_TREE, TEST_HUFFMAN_TREE_BASIC) {
  sstl::HuffmanForest<char> huffman_forest;
  EXPECT_EQ(huffman_forest.GetHaffmanTree(), nullptr);

  huffman_forest.AddItem(sstl::MakeHuffmanChar('a', 623));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('b', 99));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('c', 239));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('d', 290));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('e', 906));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('f', 111));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('g', 232));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('h', 435));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('i', 123));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('j', 657));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('k', 454));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('l', 676));
  huffman_forest.AddItem(sstl::MakeHuffmanChar('m', 34));

  LOG(INFO) << "the huffman tree:";
  auto huffman_tree = huffman_forest.GetHaffmanTree();
  auto huffman_tree2 = huffman_forest.GetHaffmanTree();

  EXPECT_EQ(huffman_tree2->Size(), 25);
  sstl::LevelTraverser::Visit(
      [](const sstl::HuffmanChar<char>& my_char) {
        printf("%c, %d, %d, ", my_char.value, my_char.weight,
               my_char.result_code->Size());
        for (int i = 0; i < my_char.result_code->Size(); ++i) {
          printf("%c", my_char.result_code->Get(i));
        }
        std::cout << std::endl;
      },
      huffman_tree->Root());

  LOG(INFO) << "the huffman table";
  auto huffman_table = huffman_forest.GetHuffmanTable();

  for (int i = 0; i < huffman_table.Size(); ++i) {
    std::cout << "index:" << i << ": " << huffman_table[i].value << " ,"
              << huffman_table[i].weight << " ,";
    for (int j = 0; j < huffman_table[i].result_code->Size(); ++j) {
      std::cout << huffman_table[i].result_code->Get(j);
    }
    std::cout << std::endl;
  }

  huffman_forest.AddItem(sstl::MakeHuffmanChar('o', 457));
  auto huffman_table3 = huffman_forest.GetHuffmanTable();
  for (int i = 0; i < huffman_table3.Size(); ++i) {
    std::cout << "index:" << i << ": " << huffman_table3[i].value << " ,"
              << huffman_table3[i].weight << " ,";
    for (int j = 0; j < huffman_table3[i].result_code->Size(); ++j) {
      std::cout << huffman_table3[i].result_code->Get(j);
    }
    std::cout << std::endl;
  }
}
