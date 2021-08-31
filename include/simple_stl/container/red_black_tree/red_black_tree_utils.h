/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: red_black_tree_utils.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"
#include "simple_stl/utility/utility.h"

namespace sstl {
struct RedBlackTreeUtils {
  // height in rb_tree is quite different from bst
  // so if we use update height API directly it will make confuse
  template <typename NodeType>
  static int UpdateBlackHeight(NodeType* my_node) {
    int now_black_height = 0;
    if (my_node->color == kBlackColor) {
      now_black_height = 1;
    }
    return (my_node->height =
                (now_black_height + Max(BinaryTreeNodeUtils::GetTreeNodeHeight(
                                            my_node->left_child),
                                        BinaryTreeNodeUtils::GetTreeNodeHeight(
                                            my_node->right_child))));
  }

  template <typename NodeType>
  static bool BlackHeightBalanced(NodeType* my_node) {
    if (BinaryTreeNodeUtils::GetTreeNodeHeight(my_node->left_child) ==
        BinaryTreeNodeUtils::GetTreeNodeHeight(my_node->right_child)) {
      if (my_node->color == kRedColor) {
        return my_node->height ==
               BinaryTreeNodeUtils::GetTreeNodeHeight(my_node->left_child);
      } else {
        return my_node->height ==
               (BinaryTreeNodeUtils::GetTreeNodeHeight(my_node->left_child) +
                1);
      }
    }
    return false;
  }
};
}  // namespace sstl
