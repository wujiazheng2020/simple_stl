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

namespace sstl {
template <typename FirstType, typename SecondType>
struct Pair {
  FirstType first;
  SecondType second;

  // in precise, this is a key not pair
  // but we can create a real pair class extends key class
  // but we seldom use operate< to compare to other in real usage
  bool operator<(const Pair<FirstType, SecondType>& other_pair) {
    return first < other_pair.first;
  }

  bool operator==(const Pair<FirstType, SecondType>& other_pair) {
    return first == other_pair.first;
  }

  bool operator!=(const Pair<FirstType, SecondType>& other_pair) {
    return first != other_pair.first;
  }

  bool operator>(const Pair<FirstType, SecondType>& other_pair) {
    return first > other_pair.first;
  }
};

template <typename FirstType, typename SecondType>
static Pair<FirstType, SecondType> MakePair(const FirstType& first,
                                            const SecondType& second) {
  Pair<FirstType, SecondType> pair;
  pair.first = first;
  pair.second = second;
  return pair;
}
}  // namespace sstl
