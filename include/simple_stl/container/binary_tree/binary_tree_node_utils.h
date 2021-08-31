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

#include "simple_stl/utility/utility.h"

namespace sstl {
// for red black tree
constexpr const char kRedColor = 'r';
constexpr const char kBlackColor = 'b';

struct BinaryTreeNodeUtils {
  template <typename TreeNode>
  static int GetTreeNodeHeight(TreeNode* tree_node) {
    if (tree_node) {
      return tree_node->height;
    } else {
      return -1;
    }
  }

  template <typename TreeNode>
  static int UpdateHeight(TreeNode* node) {
    return (node->height = 1 + Max(GetTreeNodeHeight(node->left_child),
                                   GetTreeNodeHeight(node->right_child)));
  }

  template <typename TreeNode>
  static void UpdateHeightAbove(TreeNode* node) {
    while (node) {
      UpdateHeight(node);
      node = node->parent;
    }
  }

  // height diff
  template <typename TreeNode>
  static int BalanceFactorInHeight(TreeNode* tree_node) {
    return GetTreeNodeHeight(tree_node->left_child) -
           GetTreeNodeHeight(tree_node->right_child);
  }

  template <typename TreeNode>
  static bool IsAvlBalanced(TreeNode* tree_node) {
    return (BalanceFactorInHeight(tree_node) <= 1 &&
            BalanceFactorInHeight(tree_node) >= -1);
  }

  template <typename TreeNode>
  static bool IsRootNode(TreeNode* node) {
    if (node->parent) {
      return false;
    } else {
      return true;
    }
  }

  template <typename TreeNode>
  static bool IsLeftChild(TreeNode* node) {
    if (!IsRootNode(node) && node == node->parent->left_child) {
      return true;
    } else {
      return false;
    }
  }

  template <typename TreeNode>
  static bool IsRightChild(TreeNode* node) {
    if (!IsRootNode(node) && node == node->parent->right_child) {
      return true;
    } else {
      return false;
    }
  }

  template <typename TreeNode>
  static void DepartNodeFromOriginTree(TreeNode* node) {
    if (IsRightChild(node)) {
      node->parent->right_child = nullptr;
    } else if (IsLeftChild(node)) {
      node->parent->left_child = nullptr;
    }
  }
};

}  // namespace sstl
