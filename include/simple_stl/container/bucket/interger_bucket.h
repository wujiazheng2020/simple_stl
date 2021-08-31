/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: bucket.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
// for effeciency we don't use the hash map
class IntergerBucket {
 public:
  IntergerBucket() : bucket_(new int[10]) {
    for (int i = 0; i < 10; ++i) {
      bucket_[i] = 0;
    }
  }
  ~IntergerBucket() {}

  void Set(const int& index) { ++bucket_[index]; }

  bool Test(const int& index) { return bucket_[index]; }

  // return the times you had set
  int GetAcc(const int& index) { return bucket_[index]; }

 private:
  int* bucket_;
};
}  // namespace sstl
