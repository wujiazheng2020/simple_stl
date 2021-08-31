/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: binary_search_tree_utils.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"

namespace sstl {
struct RebalanceUtils {
 public:
  template <typename TreeNode>
  static TreeNode* RebalanceToRoot(TreeNode* now_node) {
    TreeNode* son_node = now_node;
    TreeNode* mid_node = now_node;

    while (son_node && son_node->parent && son_node->parent->parent) {
      if (!BinaryTreeNodeUtils::IsAvlBalanced(son_node->parent->parent)) {
        mid_node = RotateAt(son_node);
        if (mid_node->parent) {
          BinaryTreeNodeUtils::UpdateHeight(mid_node->parent);
        }
      }
      son_node = son_node->parent;
    }
    return mid_node;
  }

  template <typename TreeNode>
  static TreeNode* RotateAt(TreeNode* now_node) {
    TreeNode* parent_node = now_node->parent;
    TreeNode* parent_of_parent = now_node->parent->parent;

    if (BinaryTreeNodeUtils::IsLeftChild(parent_node)) {
      if (BinaryTreeNodeUtils::IsLeftChild(now_node)) {
        // 1.1 L-L
        if (parent_of_parent->parent) {
          if (BinaryTreeNodeUtils::IsLeftChild(parent_of_parent)) {
            parent_of_parent->parent->left_child = parent_node;
          } else {
            parent_of_parent->parent->right_child = parent_node;
          }
        }
        parent_node->parent = parent_of_parent->parent;

        return ThreeNodeFourSubTreeRebuild(
            now_node, parent_node, parent_of_parent, now_node->left_child,
            now_node->right_child, parent_node->right_child,
            parent_of_parent->right_child);
      } else {
        // 1.2 L->R
        if (parent_of_parent->parent) {
          if (BinaryTreeNodeUtils::IsLeftChild(parent_of_parent)) {
            parent_of_parent->parent->left_child = now_node;
          } else {
            parent_of_parent->parent->right_child = now_node;
          }
        }
        now_node->parent = parent_of_parent->parent;

        return ThreeNodeFourSubTreeRebuild(
            parent_node, now_node, parent_of_parent, parent_node->left_child,
            now_node->left_child, now_node->right_child,
            parent_of_parent->right_child);
      }
    } else {
      if (BinaryTreeNodeUtils::IsLeftChild(now_node)) {
        // 1.3 R->L
        if (parent_of_parent->parent) {
          if (BinaryTreeNodeUtils::IsLeftChild(parent_of_parent)) {
            parent_of_parent->parent->left_child = now_node;
          } else {
            parent_of_parent->parent->right_child = now_node;
          }
        }
        now_node->parent = parent_of_parent->parent;

        return ThreeNodeFourSubTreeRebuild(
            parent_of_parent, now_node, parent_node,
            parent_of_parent->left_child, now_node->left_child,
            now_node->right_child, parent_node->right_child);
      } else {
        // 1.4 R->R
        if (parent_of_parent->parent) {
          if (BinaryTreeNodeUtils::IsLeftChild(parent_of_parent)) {
            parent_of_parent->parent->left_child = parent_node;
          } else {
            parent_of_parent->parent->right_child = parent_node;
          }
        }
        parent_node->parent = parent_of_parent->parent;

        return ThreeNodeFourSubTreeRebuild(
            parent_of_parent, parent_node, now_node,
            parent_of_parent->left_child, parent_node->left_child,
            now_node->left_child, now_node->right_child);
      }
    }

    return now_node;
  }

 private:
  template <typename TreeNode>
  static TreeNode* ThreeNodeFourSubTreeRebuild(TreeNode* a, TreeNode* b,
                                               TreeNode* c, TreeNode* T0,
                                               TreeNode* T1, TreeNode* T2,
                                               TreeNode* T3) {
    a->left_child = T0;
    a->right_child = T1;
    c->left_child = T2;
    c->right_child = T3;

    b->left_child = a;
    b->right_child = c;
    a->parent = b;
    c->parent = b;
    if (T0) {
      T0->parent = a;
    }
    if (T1) {
      T1->parent = a;
    }
    if (T2) {
      T2->parent = c;
    }
    if (T3) {
      T3->parent = c;
    }
    BinaryTreeNodeUtils::UpdateHeight(a);
    BinaryTreeNodeUtils::UpdateHeight(c);
    BinaryTreeNodeUtils::UpdateHeight(b);
    return b;
  }
};

}  // namespace sstl
