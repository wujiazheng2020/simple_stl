/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: splay_tree.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <memory>

#include "simple_stl/container/binary_search_tree/binary_search_tree.h"
#include "simple_stl/container/binary_tree/binary_tree_node_utils.h"

namespace sstl {
template <typename DataType>
class SplayTree : public BinarySearchTree<DataType> {
 public:
  SplayTree() {}
  ~SplayTree() {}

  using BinarySearchTree<DataType>::SetRoot;
  using BinaryTree<DataType>::SetSize;

  // time complexity:O(h)
  BinaryTreeNode<DataType>* Search(const DataType& search_elem) {
    BinaryTreeNode<DataType>* father_of_hit;
    return Search(search_elem, &father_of_hit);
  }

  // time complexity:O(h)
  BinaryTreeNode<DataType>* Insert(const DataType& elem) override {
    BinaryTreeNode<DataType>* now_node = Search(elem);
    if (!now_node) {
      this->InsertAsRoot(elem);
      return this->Root();
    }
    if (now_node->data == elem) {
      return this->Root();
    } else if (now_node->data < elem) {
      BinaryTreeNode<DataType>* new_node = new BinaryTreeNode<DataType>(elem);
      new_node->right_child = this->Root()->right_child;
      new_node->left_child = this->Root();
      this->Root()->right_child = nullptr;

      if (new_node->right_child) {
        new_node->right_child->parent = new_node;
      }
      new_node->left_child->parent = new_node;
      this->SetRoot(new_node);
      this->SetSize(this->Size() + 1);
      BinaryTreeNodeUtils::UpdateHeight(new_node);
    } else {
      // now_node->data > elem
      BinaryTreeNode<DataType>* new_node = new BinaryTreeNode<DataType>(elem);
      new_node->left_child = this->Root()->left_child;
      new_node->right_child = this->Root();
      this->Root()->left_child = nullptr;

      if (new_node->left_child) {
        new_node->left_child->parent = new_node;
      }
      new_node->right_child->parent = new_node;
      this->SetRoot(new_node);
      BinaryTreeNodeUtils::UpdateHeight(new_node);
      this->SetSize(this->Size() + 1);
    }
    return now_node;
  }

  // time complexity:O(h)
  BinaryTreeNode<DataType>* Remove(const DataType& elem) override {
    BinaryTreeNode<DataType>* now_node = Search(elem);
    if (this->Size() == 1) {
      delete this->Root();
      this->SetRoot(nullptr);
      this->SetSize(0);
      return nullptr;
    }
    if (!now_node || now_node->data != elem) {
      return nullptr;
    }
    if (!now_node->left_child) {
      now_node->right_child->parent = nullptr;
      this->SetRoot(now_node->right_child);
    } else if (!now_node->right_child) {
      now_node->left_child->parent = nullptr;
      this->SetRoot(now_node->left_child);
    } else {
      // depart
      BinaryTreeNode<DataType>* left_node = now_node->left_child;
      left_node->parent = nullptr;
      now_node->left_child = nullptr;

      BinaryTreeNode<DataType>* right_node = now_node->right_child;
      right_node->parent = nullptr;
      now_node->right_child = nullptr;
      this->SetRoot(right_node);

      // splay
      Search(now_node->data);
      this->Root()->left_child = left_node;
      if (this->Root()->left_child) {
        this->Root()->left_child->parent = this->Root();
      }
    }
    delete now_node;
    now_node = nullptr;
    this->SetSize(this->Size() - 1);
    BinaryTreeNodeUtils::UpdateHeight(this->Root());
    return this->Root();
  }

  // return new_root
  BinaryTreeNode<DataType>* Search(const DataType& search_elem,
                                   BinaryTreeNode<DataType>** father_of_hit) {
    BinaryTreeNode<DataType>* now_node =
        BinarySearchTree<DataType>::Search(search_elem, father_of_hit);

    if (!now_node) {
      now_node = *father_of_hit;
    }

    if (!now_node) {
      return nullptr;
    }
    BinaryTreeNode<DataType>* new_root = Splay(now_node);
    this->SetRoot(new_root);
    return new_root;
  }

  // serialize the tree to output stream
  void Serialize(std::ostream& os) const {
    SerializeNode(this->Root(), os);
    int sz = this->Size();
    os.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
  }

  // deserialize the tree from input stream
  static std::unique_ptr<SplayTree<DataType>> Deserialize(std::istream& is) {
    auto tree = std::make_unique<SplayTree<DataType>>();
    auto* root = DeserializeNode(is);
    tree->SetRoot(root);
    int sz;
    is.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    tree->SetSize(sz);
    return tree;
  }

  void create(std::istream& is) {
    // 1) 删除当前所有节点
    if (this->Root()) {
      // BinaryTree::Remove 会递归删除以 Root() 为根的所有节点
      this->Reset();
    }

    // 2) 反序列化到一个临时树
    auto temp = Deserialize(is);

    // 3) “偷过来”根节点指针和树大小
    this->SetRoot(temp->Root());
    this->SetSize(temp->Size());

    // 4) 防止 temp 析构时把这些节点重复删掉
    temp->SetRoot(nullptr);
    temp->SetSize(0);
  }

 private:
  static void SerializeNode(BinaryTreeNode<DataType>* node, std::ostream& os) {
    bool has = (node != nullptr);
    os.write(reinterpret_cast<const char*>(&has), sizeof(has));
    if (!has) return;
    // 写节点数据
    os.write(reinterpret_cast<const char*>(&node->data), sizeof(DataType));
    // 递归
    SerializeNode(node->left_child, os);
    SerializeNode(node->right_child, os);
  }

  // 递归读节点
  static BinaryTreeNode<DataType>* DeserializeNode(std::istream& is) {
    bool has = false;
    is.read(reinterpret_cast<char*>(&has), sizeof(has));
    if (!has) return nullptr;
    DataType data;
    is.read(reinterpret_cast<char*>(&data), sizeof(DataType));
    auto* node = new BinaryTreeNode<DataType>(data);
    node->left_child = DeserializeNode(is);
    if (node->left_child) node->left_child->parent = node;
    node->right_child = DeserializeNode(is);
    if (node->right_child) node->right_child->parent = node;
    BinaryTreeNodeUtils::UpdateHeight(node);
    return node;
  }

  static BinaryTreeNode<DataType>* Splay(BinaryTreeNode<DataType>* now_node) {
    BinaryTreeNode<DataType>* son_node = now_node;
    while (son_node && son_node->parent && son_node->parent->parent) {
      BinaryTreeNode<DataType>* father_node3 = son_node->parent->parent->parent;
      BinaryTreeNode<DataType>* father_node2 = son_node->parent->parent;
      BinaryTreeNode<DataType>* father_node1 = son_node->parent;
      if (father_node3) {
        if (BinaryTreeNodeUtils::IsLeftChild(father_node2)) {
          father_node3->left_child = son_node;
        } else {
          father_node3->right_child = son_node;
        }
      }

      if (BinaryTreeNodeUtils::IsLeftChild(son_node)) {
        if (BinaryTreeNodeUtils::IsLeftChild(father_node1)) {
          // L->L
          // update son
          father_node2->left_child = father_node1->right_child;
          father_node1->left_child = son_node->right_child;
          father_node1->right_child = father_node2;
          son_node->right_child = father_node1;

          // update parent
          if (father_node2->left_child) {
            father_node2->left_child->parent = father_node2;
          }
          if (father_node1->left_child) {
            father_node1->left_child->parent = father_node1;
          }
          father_node1->right_child->parent = father_node1;
          son_node->right_child->parent = son_node;

        } else {
          // L->R
          // update son
          father_node1->left_child = son_node->right_child;
          father_node2->right_child = son_node->left_child;
          son_node->left_child = father_node2;
          son_node->right_child = father_node1;

          // update parent
          if (father_node1->left_child) {
            father_node1->left_child->parent = father_node1;
          }
          if (father_node2->right_child) {
            father_node2->right_child->parent = father_node2;
          }
          son_node->left_child->parent = son_node;
          son_node->right_child->parent = son_node;
        }
      } else {
        if (BinaryTreeNodeUtils::IsLeftChild(father_node1)) {
          // R->L
          // update son
          father_node1->right_child = son_node->left_child;
          father_node2->left_child = son_node->right_child;
          son_node->right_child = father_node2;
          son_node->left_child = father_node1;

          // update parent
          if (father_node1->right_child) {
            father_node1->right_child->parent = father_node1;
          }
          if (father_node2->left_child) {
            father_node2->left_child->parent = father_node2;
          }
          son_node->right_child->parent = son_node;
          son_node->left_child->parent = son_node;
        } else {
          // R->R
          // update son
          father_node2->right_child = father_node1->left_child;
          father_node1->right_child = son_node->left_child;
          father_node1->left_child = father_node2;
          son_node->left_child = father_node1;

          // update parent
          if (father_node2->right_child) {
            father_node2->right_child->parent = father_node2;
          }
          if (father_node1->right_child) {
            father_node1->right_child->parent = father_node1;
          }
          father_node1->left_child->parent = father_node1;
          son_node->left_child->parent = son_node;
        }
      }

      BinaryTreeNodeUtils::UpdateHeight(father_node2);
      BinaryTreeNodeUtils::UpdateHeight(father_node1);
      BinaryTreeNodeUtils::UpdateHeight(son_node);

      son_node->parent = father_node3;
      if (father_node3) {
        BinaryTreeNodeUtils::UpdateHeight(father_node3);
      }
    }
    BinaryTreeNode<DataType>* father_node1 = son_node->parent;
    if (father_node1) {
      if (BinaryTreeNodeUtils::IsLeftChild(son_node)) {
        father_node1->left_child = son_node->right_child;
        son_node->right_child = father_node1;

        if (father_node1->left_child) {
          father_node1->left_child->parent = father_node1;
        }
        son_node->right_child->parent = son_node;
      } else {
        father_node1->right_child = son_node->left_child;
        son_node->left_child = father_node1;

        if (father_node1->right_child) {
          father_node1->right_child->parent = father_node1;
        }
        son_node->left_child->parent = son_node;
      }
      BinaryTreeNodeUtils::UpdateHeight(father_node1);
      BinaryTreeNodeUtils::UpdateHeight(son_node);
    }
    son_node->parent = nullptr;
    return son_node;
  }
};
}  // namespace sstl
