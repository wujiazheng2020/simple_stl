/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vector.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/vector/allocator/double_times_allocator.h"
#include "simple_stl/container/vector/allocator/linear_allocator.h"

namespace sstl {
template <typename DataType, typename Allocator = DoubleTimesAllocator>
class Vector {
 public:
  Vector() : capcity_(1), size_(0), is_ordered_(true) {
    elem_ = new DataType[1];
  }

  explicit Vector(const int& capcity) {
    size_ = 0;
    capcity_ = capcity;
    elem_ = new DataType[capcity_];
    is_ordered_ = true;
  }

  Vector(const int& capcity, const DataType& data) {
    capcity_ = capcity;
    capcity_ <<= 1;
    elem_ = new DataType[capcity_];
    for (int i = 0; i < capcity; ++i) {
      elem_[i] = data;
    }
    size_ = capcity;
    is_ordered_ = true;
  }

  // copy from [start_rank, end_rank)
  Vector(const Vector<DataType>& other_vec, const int& start_rank,
         const int& end_rank) {
    CopyFrom(other_vec.elem_, start_rank, end_rank);
    is_ordered_ = other_vec.is_ordered_;
  }

  // deep copy
  Vector(const Vector<DataType>& other_vec) {
    CopyFrom(other_vec.elem_, 0, other_vec.size_);
    is_ordered_ = other_vec.is_ordered_;
  }

  ~Vector() { delete[] elem_; }

  bool Empty() const { return size_ == 0 ? true : false; }

  const int& Size() const { return size_; }

  const int& Capcity() const { return capcity_; }

  DataType& operator[](const int& rank) {
    is_ordered_ = false;
    return elem_[rank];
  }

  const DataType& operator[](const int& rank) const { return elem_[rank]; }

  // deep copy
  void operator=(const Vector<DataType>& other_vec) {
    CopyFrom(other_vec.elem_, 0, other_vec.size_);
    is_ordered_ = other_vec.is_ordered_;
  }

  int Clear() {
    DataType* old_elem = elem_;
    int old_size = size_;
    elem_ = new DataType[1];
    capcity_ = 1;
    size_ = 0;
    is_ordered_ = true;
    delete[] old_elem;
    return old_size;
  }

  const DataType& Get(const int& rank) const { return elem_[rank]; }

  // size must > 1
  void Put(const int& rank, const DataType& elem) {
    elem_[rank] = elem;

    is_ordered_ = false;
  }

  // return rank
  int Insert(const int& rank, const DataType& elem) {
    Expand();

    for (int i = size_; i > rank; --i) {
      elem_[i] = elem_[i - 1];
    }
    elem_[rank] = elem;
    ++size_;

    is_ordered_ = false;

    return rank;
  }

  // remove [start_rank, end_rank)
  // return delete length
  int Remove(const int& start_rank, const int& end_rank) {
    int delete_size = end_rank - start_rank;
    for (int i = end_rank; i < size_; ++i) {
      elem_[i - delete_size] = elem_[i];
    }

    size_ -= delete_size;
    Shrink();
    return delete_size;
  }

  // return 1
  int Remove(const int& rank) { return Remove(rank, rank + 1); }

  // when using search you should confrim it is ordered
  bool CheckOrdered() {
    if (is_ordered_) {
      return true;
    } else {
      is_ordered_ = true;
      for (int i = 0; i < size_ - 1; ++i) {
        if (elem_[i + 1] < elem_[i]) {
          is_ordered_ = false;
          return false;
        }
      }
      return true;
    }
  }

  const bool& CheckOrdered() const { return is_ordered_; }

  // for std stl
  // return size
  int PushBack(const DataType& elem) { return Insert(size_, elem); }

  // return the delete elem
  DataType PopBack() {
    --size_;
    DataType elem = elem_[size_];
    Shrink();
    return elem;
  }

  DataType& Tail() { return elem_[size_ - 1]; }

  const DataType& Tail() const { return elem_[size_ - 1]; }

 private:
  void Expand() {
    if (size_ < capcity_ - 1) {
      return;
    } else {
      elem_ = Allocator::Malloc(elem_, &capcity_);
    }
  }

  // if lower than 25%
  void Shrink() {
    if (capcity_ > 4 * size_ && capcity_ > 1) {
      elem_ = Allocator::ReleaseMemory(elem_, &capcity_);
    }
  }

  // [start_rank, end_rank)
  void CopyFrom(DataType* old_elem, const int& start_rank,
                const int& end_rank) {
    capcity_ = end_rank - start_rank;
    size_ = capcity_;
    capcity_ <<= 1;
    elem_ = new DataType[capcity_];
    for (int i = start_rank; i < end_rank; ++i) {
      elem_[i - start_rank] = old_elem[i];
    }
  }

 private:
  DataType* elem_;
  int capcity_;
  int size_;

  bool is_ordered_;
};

}  // namespace sstl
