/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: binary_search_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree.h"

namespace sstl {
// the container is algorithm itself, so we don't need to depart it to algorithm
template <typename DataType>
class BinarySearchTree : public BinaryTree<DataType> {
 public:
  BinarySearchTree() {}
  ~BinarySearchTree() {}

  // time complexity:O(h)
  virtual BinaryTreeNode<DataType>* Search(const DataType& search_elem) const {
    BinaryTreeNode<DataType>* father_of_hit;
    return Search(search_elem, &father_of_hit);
  }

  // time complexity:O(h)
  virtual BinaryTreeNode<DataType>* Insert(const DataType& elem) {
    BinaryTreeNode<DataType>* father_of_hit = nullptr;
    BinaryTreeNode<DataType>* now_node = Search(elem, &father_of_hit);
    if (!now_node) {
      if (!this->Root()) {
        this->InsertAsRoot(elem);
        BinaryTreeNodeUtils::UpdateHeight(this->Root());
        return this->Root();
      } else {
        if (father_of_hit->data > elem) {
          this->InsertAsLeftChild(father_of_hit, elem);
          BinaryTreeNodeUtils::UpdateHeight(father_of_hit);
          return father_of_hit->left_child;
        } else {
          this->InsertAsRightChild(father_of_hit, elem);
          BinaryTreeNodeUtils::UpdateHeight(father_of_hit);
          return father_of_hit->right_child;
        }
      }
    }
    return now_node;
  }

  // time complexity:O(h)
  virtual BinaryTreeNode<DataType>* Remove(const DataType& elem) {
    BinaryTreeNode<DataType>* father_of_hit = nullptr;
    BinaryTreeNode<DataType>* now_node = Search(elem, &father_of_hit);
    if (!now_node) {
      return father_of_hit;
    }
    RemoveAt(now_node, &father_of_hit);
    BinaryTreeNodeUtils::UpdateHeightAbove(father_of_hit);
    return father_of_hit;
  }

  // fail return nullptr
  // else return match node
  // Warning: this function must be use carefully
  // it is for convenient, but it should be a private func as normal
  virtual BinaryTreeNode<DataType>* Search(
      const DataType& search_elem,
      BinaryTreeNode<DataType>** father_of_hit) const {
    *father_of_hit = nullptr;
    if (!this->Root() || this->Root()->data == search_elem) {
      return this->Root();
    }
    BinaryTreeNode<DataType>* now_node = this->Root();
    while (now_node) {
      if (now_node->data > search_elem) {
        *father_of_hit = now_node;
        now_node = now_node->left_child;
      } else if (now_node->data < search_elem) {
        *father_of_hit = now_node;
        now_node = now_node->right_child;
      } else {
        // equal
        return now_node;
      }
    }
    return now_node;
  }

 protected:
  BinaryTreeNode<DataType>* RemoveAt(BinaryTreeNode<DataType>* now_node,
                                     BinaryTreeNode<DataType>** father_node) {
    BinaryTreeNode<DataType>* need_delete_node = now_node;
    BinaryTreeNode<DataType>* succ_node = nullptr;
    if (!now_node->left_child) {
      succ_node = now_node->right_child;
    } else if (!now_node->right_child) {
      succ_node = now_node->left_child;
    } else {
      need_delete_node = need_delete_node->Succ();
      DataType tmp_data = need_delete_node->data;
      need_delete_node->data = now_node->data;
      now_node->data = tmp_data;
      // it must be
      succ_node = need_delete_node->right_child;
    }
    *father_node = need_delete_node->parent;
    if (succ_node) {
      succ_node->parent = *father_node;
    }

    if (*father_node) {
      if (BinaryTreeNodeUtils::IsLeftChild(need_delete_node)) {
        (*father_node)->left_child = succ_node;
      } else {
        (*father_node)->right_child = succ_node;
      }
      delete need_delete_node;
      need_delete_node = nullptr;
      this->SetSize(this->Size() - 1);
      return succ_node;
    } else {
      // it is root
      if (succ_node) {
        this->Root()->left_child = succ_node->left_child;
        this->Root()->right_child = succ_node->right_child;
        this->Root()->data = succ_node->data;

        if (this->Root()->left_child) {
          this->Root()->left_child->parent = this->Root();
        }
        if (this->Root()->right_child) {
          this->Root()->right_child->parent = this->Root();
        }
        delete succ_node;
        succ_node = nullptr;
        this->SetSize(this->Size() - 1);
        return this->Root();
      } else {
        BinaryTree<DataType>::Remove(this->Root());
        return nullptr;
      }
    }
  }
};
}  // namespace sstl
