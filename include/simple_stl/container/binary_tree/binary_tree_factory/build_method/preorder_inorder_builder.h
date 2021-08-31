/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: preorder_inorder_builder.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/vector_algorithm/finder/vector_finder.h"
#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct PreorderInorderBuilder {
  template <typename DataType>
  static BinaryTree<DataType>* BuildTree(
      const Vector<DataType>& pre_seqence,
      const Vector<DataType>& inorder_sequence) {
    if (!pre_seqence.Empty() && !inorder_sequence.Empty()) {
      BinaryTree<DataType>* my_tree = new BinaryTree<DataType>();
      my_tree->InsertAsRoot(pre_seqence[0]);
      int inorder_mid = VectorFinder::Find(inorder_sequence, pre_seqence[0]);
      int pre_mid = inorder_mid + 1;
      BuildLeftTree(my_tree->Root(), pre_seqence, inorder_sequence, 1, 0,
                    inorder_mid);
      BuildRightTree(my_tree->Root(), pre_seqence, inorder_sequence, pre_mid,
                     inorder_mid + 1, inorder_sequence.Size());
      my_tree->UpdateSize();
      return my_tree;
    } else {
      return nullptr;
    }
  }

 private:
  template <typename DataType>
  static void BuildLeftTree(BinaryTreeNode<DataType>* my_node,
                            const Vector<DataType>& pre_seqence,
                            const Vector<DataType>& inorder_sequence,
                            const int& pre_start, const int& inorder_start,
                            const int& inorder_end) {
    if (pre_start >= pre_seqence.Size() || inorder_start >= inorder_end) {
      return;
    }
    my_node->InsertAsLeftChild(pre_seqence[pre_start]);
    int inorder_mid = VectorFinder::Find(inorder_sequence, inorder_start,
                                         inorder_end, pre_seqence[pre_start]);
    int pre_mid = pre_start + inorder_mid - inorder_start + 1;
    BuildLeftTree(my_node->left_child, pre_seqence, inorder_sequence,
                  pre_start + 1, inorder_start, inorder_mid);
    BuildRightTree(my_node->left_child, pre_seqence, inorder_sequence, pre_mid,
                   inorder_mid + 1, inorder_end);
  }

  template <typename DataType>
  static void BuildRightTree(BinaryTreeNode<DataType>* my_node,
                             const Vector<DataType>& pre_seqence,
                             const Vector<DataType>& inorder_sequence,
                             const int& pre_start, const int& inorder_start,
                             const int& inorder_end) {
    if (pre_start >= pre_seqence.Size() || inorder_start >= inorder_end) {
      return;
    }
    my_node->InsertAsRightChild(pre_seqence[pre_start]);
    int inorder_mid = VectorFinder::Find(inorder_sequence, inorder_start,
                                         inorder_end, pre_seqence[pre_start]);
    int pre_mid = pre_start + inorder_mid - inorder_start + 1;
    BuildLeftTree(my_node->right_child, pre_seqence, inorder_sequence,
                  pre_start + 1, inorder_start, inorder_mid);
    BuildRightTree(my_node->right_child, pre_seqence, inorder_sequence, pre_mid,
                   inorder_mid + 1, inorder_end);
  }
};
}  // namespace sstl
