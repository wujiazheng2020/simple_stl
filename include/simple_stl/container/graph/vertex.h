/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: vertex.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include <iostream>

namespace sstl {
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VertexStatus;

template <typename VertexDataType>
struct Vertex {
  Vertex() {}
  explicit Vertex(const VertexDataType& the_data)
      : data(the_data),
        in_degree(0),
        out_degree(0),
        parent(-1),
        status(UNDISCOVERED),
        first_visit_time(-1),
        last_visit_time(-1),
        priority(0) {}
  ~Vertex() {}

  void PrintInfo() const {
    std::cout << "data:" << data << "  ,"
              << "in:" << in_degree << "  ,"
              << "out:" << out_degree << "  ,"
              << "parent:" << parent << "  ,"
              << "status:" << status << "  ,"
              << "first:" << first_visit_time << ","
              << "last:" << last_visit_time << ","
              << "prior:" << priority;
  }

  // basic
  VertexDataType data;
  int in_degree;
  int out_degree;

  // for sepecial algorithm
  int parent;  // parent id
  VertexStatus status;
  int first_visit_time;
  int last_visit_time;

  // for PFS
  int priority;
};
}  // namespace sstl
