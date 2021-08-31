/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: huffman_forest.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/postorder_traverse/postorder_traverser_common.h"
#include "simple_stl/algorithm/vector_algorithm/sorter/vector_insert_sort.h"
#include "simple_stl/container/huffman_forest/huffman_tree.h"
#include "simple_stl/container/pair/pair.h"

namespace sstl {
// here we don't use template of template
// as we see, we don't need vector to provide deleteMax API, it is costly
// so for each container, we hava the different solution
template <typename DataType>
class HuffmanForest : protected Vector<HuffmanChar<DataType>> {
 public:
  HuffmanForest() : has_init_(false), order_tree_(nullptr) {}
  ~HuffmanForest() {}

  HuffmanTree<DataType>* GetHaffmanTree() {
    if (has_init_) {
      return order_tree_;
    } else {
      if (this->Empty()) {
        return nullptr;
      }
      Vector<HuffmanTree<DataType>*> total_forest;
      VectorInsertSort::Sort(this);
      for (int i = 0; i < this->Size(); ++i) {
        HuffmanTree<DataType>* now_tree = new HuffmanTree<DataType>();
        now_tree->InsertAsRoot(this->Get(i));
        total_forest.PushBack(now_tree);
      }

      while (total_forest.Size() > 1) {
        HuffmanTree<DataType>* first_tree = total_forest.PopBack();
        HuffmanTree<DataType>* second_tree = total_forest.PopBack();
        HuffmanTree<DataType>* new_tree = new HuffmanTree<DataType>();
        new_tree->InsertAsRoot(
            MakeHuffmanChar(first_tree->Root()->data.value,
                            first_tree->Root()->data.weight +
                                second_tree->Root()->data.weight));
        new_tree->AttachAsLeftChild(new_tree->Root(), first_tree);
        new_tree->AttachAsRightChild(new_tree->Root(), second_tree);

        // insert back
        total_forest.PushBack(new_tree);
        int i = total_forest.Size() - 2;
        while (i >= 0) {
          if (total_forest[i]->Root()->data.weight >=
              new_tree->Root()->data.weight) {
            if (total_forest[i + 1] != new_tree) {
              total_forest[i + 1] = new_tree;
            }
            break;
          }
          total_forest[i + 1] = total_forest[i];
          --i;
        }
        if (i == -1) {
          total_forest[0] = new_tree;
        }
      }
      order_tree_ = total_forest.PopBack();
      order_tree_->Root()->data.result_code->PushBack('1');
      CodeEachChild(order_tree_->Root());
      has_init_ = true;
      return order_tree_;
    }
  }

  Vector<HuffmanChar<DataType>> GetHuffmanTable() {
    Vector<HuffmanChar<DataType>> vec;
    if (has_init_) {
      return huffman_table_;
    } else {
      GetHaffmanTree();
      return huffman_table_;
    }
    return vec;
  }

  void AddItem(const HuffmanChar<DataType>& elem) {
    Vector<HuffmanChar<DataType>>::PushBack(elem);
    has_init_ = false;
    if (!huffman_table_.Empty()) {
      huffman_table_.Clear();
    }
    if (order_tree_) {
      delete order_tree_;
      order_tree_ = nullptr;
    }
  }

 private:
  void CodeEachChild(BinaryTreeNode<HuffmanChar<DataType>>* node) {
    if (!node->left_child && !node->right_child) {
      huffman_table_.PushBack(node->data);
    }
    if (node->left_child) {
      *node->left_child->data.result_code = *node->data.result_code;
      node->left_child->data.result_code->PushBack('1');
      CodeEachChild(node->left_child);
    }
    if (node->right_child) {
      *node->right_child->data.result_code = *node->data.result_code;
      node->right_child->data.result_code->PushBack('0');
      CodeEachChild(node->right_child);
    }
  }

 private:
  bool has_init_;
  Vector<HuffmanChar<DataType>> huffman_table_;
  HuffmanTree<DataType>* order_tree_;
};
}  // namespace sstl
