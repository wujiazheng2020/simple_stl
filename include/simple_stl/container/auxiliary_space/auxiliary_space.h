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

namespace sstl {
// this is an abstract class
// for simplification, we achieve it just like vector
template <typename DataType>
class AuxiliarySpace {
 public:
  explicit AuxiliarySpace(const int& size) { CreateSpace(size); }
  ~AuxiliarySpace() {
    if (elem_) {
      DeleteSpace();
    }
  }

  DataType* Elem() { return elem_; }

  void SetSize(const int& size) { size_ = size; }

 private:
  void CreateSpace(const int& size) { elem_ = new DataType[size]; }
  void DeleteSpace() { delete[] elem_; }

 private:
  DataType* elem_;
  int size_;
};
}  // namespace sstl
