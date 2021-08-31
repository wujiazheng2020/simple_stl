/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: red_black_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/binary_search_tree/binary_search_tree_utils.h"
#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"
#include "simple_stl/container/red_black_tree/red_black_tree_utils.h"

namespace sstl {
template <typename DataType>
class RedBlackTree : public BinarySearchTree<DataType> {
 public:
  RedBlackTree() {}
  ~RedBlackTree() {}

  BinaryTreeNode<DataType>* Insert(const DataType& elem) override {
    BinaryTreeNode<DataType>* father_of_hit = nullptr;
    BinaryTreeNode<DataType>* now_node = this->Search(elem, &father_of_hit);
    if (now_node) {
      return nullptr;
    }

    // the different is we don't update height until color error fix
    // is root
    if (!father_of_hit) {
      // now_node is root
      now_node = new BinaryTreeNode<DataType>(elem);
      now_node->color = kBlackColor;
      ++now_node->height;
      this->SetRoot(now_node);
    } else {
      // now_node has father
      // default insert red node
      if (father_of_hit->data > elem) {
        father_of_hit->InsertAsLeftChild(elem);
        now_node = father_of_hit->left_child;
      } else {
        father_of_hit->InsertAsRightChild(elem);
        now_node = father_of_hit->right_child;
      }
      now_node->height = -1;
      SolveDoubleRed(now_node);
    }
    this->SetSize(this->Size() + 1);
    return now_node;
  }

  BinaryTreeNode<DataType>* Remove(const DataType& elem) override {
    BinaryTreeNode<DataType>* father_of_hit = nullptr;
    BinaryTreeNode<DataType>* now_node = this->Search(elem, &father_of_hit);
    if (!now_node) {
      return nullptr;
    }
    BinaryTreeNode<DataType>* succ_node =
        BinarySearchTree<DataType>::RemoveAt(now_node, &father_of_hit);

    // 1. if delete root
    // succ maybe red or black
    // change succ to black to comfirm the blackheight equal
    if (!father_of_hit) {
      if (this->Root()) {
        this->Root()->color = kBlackColor;
        RedBlackTreeUtils::UpdateBlackHeight(this->Root());
        return this->Root();
      } else {
        return nullptr;
      }
    }

    // 2. succ is not root, father black balanced
    // it appear when delete_node is red
    if (RedBlackTreeUtils::BlackHeightBalanced(father_of_hit)) {
      return succ_node;
    }

    // 3. succ_node is red
    // it appear when delete_node is black
    if (succ_node && succ_node->color == kRedColor) {
      succ_node->color = kBlackColor;
      ++succ_node->height;
      return succ_node;
    }

    // 5. succ_node is all black
    // it appear when delete_node and succ_node is both black
    SolveDoubleBlack(succ_node, father_of_hit);
    return succ_node;
  }

 private:
  // what is double red?
  // it imply now_node and father_node is both red
  // if one of which is black, you don't need to do this
  void SolveDoubleRed(BinaryTreeNode<DataType>* now_node) {
    if (!now_node->parent || !now_node->parent->parent) {
      return;
    }
    // 0. not double red
    if (now_node->parent->color == kBlackColor) {
      return;
    }
    BinaryTreeNode<DataType>* father_node = now_node->parent;
    BinaryTreeNode<DataType>* father_of_father = father_node->parent;

    BinaryTreeNode<DataType>* uncle_node;
    if (BinaryTreeNodeUtils::IsLeftChild(father_node)) {
      uncle_node = father_of_father->right_child;
    } else {
      uncle_node = father_of_father->left_child;
    }

    // 1. uncle is black or nullptr
    if (!uncle_node || uncle_node->color == kBlackColor) {
      // now_node and father_node at the same side
      if (BinaryTreeNodeUtils::IsLeftChild(now_node) ==
          BinaryTreeNodeUtils::IsLeftChild(father_node)) {
        father_node->color = kBlackColor;
      } else {
        now_node->color = kBlackColor;
      }
      father_of_father->color = kRedColor;
      BinaryTreeNode<DataType>* mid_node = RebalanceUtils::RotateAt(now_node);
      if (!mid_node->parent) {
        this->SetRoot(mid_node);
      }
      if (mid_node->left_child) {
        RedBlackTreeUtils::UpdateBlackHeight(mid_node->left_child);
      }
      if (mid_node->right_child) {
        RedBlackTreeUtils::UpdateBlackHeight(mid_node->right_child);
      }
      RedBlackTreeUtils::UpdateBlackHeight(mid_node);
    } else {
      // 2. uncle is red
      father_node->color = kBlackColor;
      uncle_node->color = kBlackColor;

      ++father_node->height;
      ++uncle_node->height;
      if (father_of_father != this->Root()) {
        father_of_father->color = kRedColor;
      } else {
        ++father_of_father->height;
      }

      SolveDoubleRed(father_of_father);
    }
  }

  // what is double black?
  // it imply now_node and succ_node is both black
  // if one of which is red, it just need one times operate
  void SolveDoubleBlack(BinaryTreeNode<DataType>* succ_node,
                        BinaryTreeNode<DataType>* father) {
    // it must have father(notice)
    BinaryTreeNode<DataType>* father_node = father;
    if (succ_node) {
      father_node = succ_node->parent;
    } else {
      father_node = father;
    }
    if (!father_node) {
      return;
    }
    BinaryTreeNode<DataType>* brother_node;
    if (succ_node == father_node->left_child) {
      brother_node = father_node->right_child;
    } else {
      brother_node = father_node->left_child;
    }
    // and the brother must hava one black son
    if (!brother_node) {
      return;
    }
    if (brother_node->color == kBlackColor) {
      BinaryTreeNode<DataType>* brother_son = nullptr;
      if (brother_node->right_child &&
          brother_node->right_child->color == kRedColor) {
        brother_son = brother_node->right_child;
      }
      // left first
      if (brother_node->left_child &&
          brother_node->left_child->color == kRedColor) {
        brother_son = brother_node->left_child;
      }
      // 1. BB-1: brother is black, one of the brother_son is red
      if (brother_son) {
        char father_color = father_node->color;
        BinaryTreeNode<DataType>* mid_node =
            RebalanceUtils::RotateAt(brother_son);
        if (!mid_node->parent) {
          this->SetRoot(mid_node);
        }
        if (mid_node->left_child) {
          mid_node->left_child->color = kBlackColor;
          RedBlackTreeUtils::UpdateBlackHeight(mid_node->left_child);
        }
        if (mid_node->right_child) {
          mid_node->right_child->color = kBlackColor;
          RedBlackTreeUtils::UpdateBlackHeight(mid_node->right_child);
        }
        mid_node->color = father_color;
        RedBlackTreeUtils::UpdateBlackHeight(mid_node);
      } else {
        // 2. BB-2: brother is black, none of the brother_son is red
        brother_node->color = kRedColor;
        --brother_node->height;
        if (father_node->color == kRedColor) {
          // 2.1 BB-2R father is red
          father_node->color = kBlackColor;

        } else {
          // 2.1 BB-2B father is black
          --father_node->height;
          SolveDoubleBlack(father_node, nullptr);
        }
      }
    } else {
      // 3. BB-3: brother is red
      brother_node->color = kBlackColor;
      father_node->color = kRedColor;
      BinaryTreeNode<DataType>* brother_son = nullptr;
      if (BinaryTreeNodeUtils::IsLeftChild(brother_node)) {
        brother_son = brother_node->left_child;
      } else {
        brother_son = brother_node->right_child;
      }
      if (brother_son) {
        BinaryTreeNode<DataType>* mid_node =
            RebalanceUtils::RotateAt(brother_son);
        if (!mid_node->parent) {
          this->SetRoot(mid_node);
        }
        if (mid_node->left_child) {
          RedBlackTreeUtils::UpdateBlackHeight(mid_node->left_child);
        }
        if (mid_node->right_child) {
          RedBlackTreeUtils::UpdateBlackHeight(mid_node->right_child);
        }
        RedBlackTreeUtils::UpdateBlackHeight(mid_node);
      }
      SolveDoubleBlack(succ_node, nullptr);
    }
  }
};
}  // namespace sstl
