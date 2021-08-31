/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: edge.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

namespace sstl {
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EdgeStatus;

template <typename EdgeDataType>
struct Edge {
  Edge() : exist(false), weight(0), status(UNDETERMINED) {}
  Edge(const EdgeDataType& the_data, int the_weight)
      : exist(true), data(the_data), weight(the_weight), status(UNDETERMINED) {}
  ~Edge() {}

  void PrintInfo(const char& mode) const {
    switch (mode) {
      case 'e':
        std::cout << exist;
        break;
      case 'd':
        std::cout << data;
        break;
      case 'w':
        std::cout << weight;
        break;
      case 's':
        std::cout << status;
        break;
      default:
        break;
    }
  }

  bool exist;
  EdgeDataType data;
  int weight;
  EdgeStatus status;
};
}  // namespace sstl
