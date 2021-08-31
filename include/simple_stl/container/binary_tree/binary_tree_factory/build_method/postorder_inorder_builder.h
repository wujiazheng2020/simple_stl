
/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: postorder_inorder_builder.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct PostorderInorderBuilder {
  template <typename DataType>
  static BinaryTree<DataType>* BuildTree(
      const Vector<DataType>& post_sequence,
      const Vector<DataType>& inorder_sequence) {
    if (!post_sequence.Empty() && !inorder_sequence.Empty()) {
      BinaryTree<DataType>* my_tree = new BinaryTree<DataType>();
      int post_end = post_sequence.Size() - 1;
      my_tree->InsertAsRoot(post_sequence[post_end]);
      int inorder_mid =
          VectorFinder::Find(inorder_sequence, post_sequence[post_end]);
      int post_mid = inorder_mid - 1;
      BuildLeftTree(my_tree->Root(), post_sequence, inorder_sequence, post_mid,
                    0, inorder_mid);
      BuildRightTree(my_tree->Root(), post_sequence, inorder_sequence,
                     post_end - 1, inorder_mid + 1, inorder_sequence.Size());
      my_tree->UpdateSize();
      return my_tree;
    } else {
      return nullptr;
    }
  }

 private:
  template <typename DataType>
  static void BuildLeftTree(BinaryTreeNode<DataType>* my_node,
                            const Vector<DataType>& post_sequence,
                            const Vector<DataType>& inorder_sequence,
                            const int& post_end, const int& inorder_start,
                            const int& inorder_end) {
    if (post_end < 0 || inorder_start >= inorder_end) {
      return;
    }
    my_node->InsertAsLeftChild(post_sequence[post_end]);

    int inorder_mid = VectorFinder::Find(inorder_sequence, inorder_start,
                                         inorder_end, post_sequence[post_end]);
    int post_mid = post_end - (inorder_end - inorder_mid + 1);
    BuildLeftTree(my_node->left_child, post_sequence, inorder_sequence,
                  post_mid, inorder_start, inorder_mid);
    BuildRightTree(my_node->left_child, post_sequence, inorder_sequence,
                   post_end - 1, inorder_mid + 1, inorder_end);
  }

  template <typename DataType>
  static void BuildRightTree(BinaryTreeNode<DataType>* my_node,
                             const Vector<DataType>& post_sequence,
                             const Vector<DataType>& inorder_sequence,
                             const int& post_end, const int& inorder_start,
                             const int& inorder_end) {
    if (post_end < 0 || inorder_start >= inorder_end) {
      return;
    }
    my_node->InsertAsRightChild(post_sequence[post_end]);
    int inorder_mid = VectorFinder::Find(inorder_sequence, inorder_start,
                                         inorder_end, post_sequence[post_end]);
    int post_mid = post_end - (inorder_end - inorder_mid + 1);
    BuildLeftTree(my_node->right_child, post_sequence, inorder_sequence,
                  post_mid, inorder_start, inorder_mid);
    BuildRightTree(my_node->right_child, post_sequence, inorder_sequence,
                   post_end - 1, inorder_mid + 1, inorder_end);
  }
};
}  // namespace sstl
