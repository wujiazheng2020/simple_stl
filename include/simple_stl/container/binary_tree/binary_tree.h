/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: auxililary_space.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/binary_tree_algorithm/traverse/inorder_traverse/inorder_traverser_common.h"
#include "simple_stl/container/binary_tree/binary_tree_node.h"

namespace sstl {
template <typename DataType>
class BinaryTree {
 public:
  BinaryTree() : size_(0), root_(nullptr) {}
  virtual ~BinaryTree() {
    RemoveAt(root_);
    size_ = 0;
    root_ = nullptr;
  }

  bool Empty() const { return !root_; }

  const int& Size() const { return size_; }

  void UpdateSize() { size_ = root_->Size(); }

  BinaryTreeNode<DataType>* Root() const { return root_; }

  BinaryTreeNode<DataType>* InsertAsRoot(const DataType& elem) {
    if (root_) {
      return nullptr;
    } else {
      ++size_;
      return root_ = new BinaryTreeNode<DataType>(elem);
    }
  }

  BinaryTreeNode<DataType>* InsertAsRightChild(BinaryTreeNode<DataType>* node,
                                               const DataType& elem) {
    node->InsertAsRightChild(elem);
    ++size_;
    BinaryTreeNodeUtils::UpdateHeightAbove(node);
    return node->right_child;
  }

  BinaryTreeNode<DataType>* InsertAsLeftChild(BinaryTreeNode<DataType>* node,
                                              const DataType& elem) {
    node->InsertAsLeftChild(elem);
    ++size_;
    BinaryTreeNodeUtils::UpdateHeightAbove(node);
    return node->left_child;
  }

  // attach another tree
  // here we change the function of which we will not clear another tree
  BinaryTreeNode<DataType>* AttachAsRightChild(
      BinaryTreeNode<DataType>* node, BinaryTree<DataType>* another_tree) {
    if (another_tree->root_) {
      node->right_child = another_tree->root_;
      node->right_child->parent = node;
    }
    size_ += another_tree->size_;
    BinaryTreeNodeUtils::UpdateHeightAbove(node);

    // don't need to clear another tree
    return node;
  }

  // here we change the function of which we will not clear another tree
  BinaryTreeNode<DataType>* AttachAsLeftChild(
      BinaryTreeNode<DataType>* node, BinaryTree<DataType>* another_tree) {
    if (another_tree->root_) {
      node->left_child = another_tree->root_;
      node->left_child->parent = node;
    }
    size_ += another_tree->size_;
    BinaryTreeNodeUtils::UpdateHeightAbove(node);

    // don't need to clear another tree
    return node;
  }

  BinaryTree<DataType>* Secede(BinaryTreeNode<DataType>* node) {
    BinaryTreeNodeUtils::DepartNodeFromOriginTree(node);
    BinaryTreeNodeUtils::UpdateHeightAbove(node->parent);

    BinaryTree<DataType>* new_tree = new BinaryTree<DataType>();
    new_tree->root_ = node;
    node->parent = nullptr;
    new_tree->size_ = node->Size();
    size_ -= new_tree->size_;
    return new_tree;
  }

  // return remove size
  int Remove(BinaryTreeNode<DataType>* node) {
    BinaryTreeNodeUtils::DepartNodeFromOriginTree(node);
    BinaryTreeNodeUtils::UpdateHeightAbove(node->parent);

    int delete_size = RemoveAt(node);
    size_ -= delete_size;
    return delete_size;
  }

  void Reset() {
    if (root_) {
      RemoveAt(root_);
      size_ = 0;
      root_ = nullptr;
    }
  }

 protected:
  void SetSize(const int& new_size) { size_ = new_size; }

  void SetRoot(BinaryTreeNode<DataType>* node) { root_ = node; }

 private:
  int RemoveAt(BinaryTreeNode<DataType>* node) {
    if (!node) return 0;
    int delete_size =
        1 + RemoveAt(node->left_child) + RemoveAt(node->right_child);
    delete node;
    if (node == root_) {
      root_ = nullptr;
    }
    return delete_size;
  }

 private:
  int size_;
  BinaryTreeNode<DataType>* root_;
};
}  // namespace sstl
