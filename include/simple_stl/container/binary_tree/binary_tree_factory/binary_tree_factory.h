/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: binary_tree_factory.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree.h"
#include "simple_stl/container/binary_tree/binary_tree_factory/build_method/preorder_inorder_builder.h"
#include "simple_stl/container/binary_tree/binary_tree_factory/build_method/postorder_inorder_builder.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {
struct BinaryTreeFactory {
  template <typename TwoSequenceBuilder, typename DataType>
  static BinaryTree<DataType>* CreateBinaryTree(
      const Vector<DataType>& first_seqence,
      const Vector<DataType>& second_sequence) {
    return TwoSequenceBuilder::BuildTree(first_seqence, second_sequence);
  }

  template <typename DataType>
  static BinaryTree<DataType>* CreateBinaryTree() {
    return new BinaryTree<DataType>();
  }
};
}  // namespace sstl
