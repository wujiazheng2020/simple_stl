/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: graph_matrix.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/container/graph/graph.h"
#include "simple_stl/container/vector/vector.h"

namespace sstl {

template <typename VertexDataType, typename EdgeDataType>
class GraphMatrix : public Graph<VertexDataType, EdgeDataType> {
 public:
  GraphMatrix() : edges_total_num_(0) {}
  virtual ~GraphMatrix() {}

  void ResetState() {
    for (int i = 0; i < vertexs_.Size(); ++i) {
      VertexStatus(i) = UNDISCOVERED;
      VertexFirstTime(i) = -1;
      VertexLastTime(i) = -1;
      VertexParent(i) = -1;
      VertexPrior(i) = 0;
      for (int j = 0; j < vertexs_.Size(); ++j) {
        if (ExistEdge(i, j)) {
          EdgeStatus(i, j) = UNDETERMINED;
        }
      }
    }
  }

  // for vertex
  virtual const int& GetTotalVertexSize() const { return vertexs_.Size(); }

  VertexDataType& VertexData(const int& index) { return vertexs_[index].data; }

  const VertexDataType& VertexData(const int& index) const {
    return vertexs_[index].data;
  }

  const int& VertexInDegree(const int& index) const {
    return vertexs_[index].in_degree;
  }

  const int& VertexOutDegree(const int& index) const {
    return vertexs_[index].out_degree;
  }

  sstl::VertexStatus& VertexStatus(const int& index) {
    return vertexs_[index].status;
  }

  int& VertexParent(const int& index) { return vertexs_[index].parent; }

  int& VertexFirstTime(const int& index) {
    return vertexs_[index].first_visit_time;
  }

  int& VertexLastTime(const int& index) {
    return vertexs_[index].last_visit_time;
  }

  int& VertexPrior(const int& index) { return vertexs_[index].priority; }

  // must be square matrix
  // o o o o o x
  // o o o o o x
  // o o o o o x
  // o o o o o x
  // o o o o o x
  // x x x x x x
  virtual int InsertVertex(const VertexDataType& vertex_data) {
    vertexs_.PushBack(Vertex<VertexDataType>(vertex_data));
    Vector<Edge<EdgeDataType>> last_edge_vec;
    Edge<EdgeDataType> no_exist_edge;
    for (int i = 0; i < edges_.Size(); ++i) {
      edges_[i].PushBack(no_exist_edge);
      last_edge_vec.PushBack(no_exist_edge);
    }
    last_edge_vec.PushBack(no_exist_edge);
    edges_.PushBack(last_edge_vec);
    return edges_.Size();
  }

  // o o o x o
  // x x x x x <
  // o o o x o
  // o o o x o
  // o o o x o
  virtual VertexDataType RemoveVertex(const int& index) {
    for (int i = 0; i < edges_.Size(); ++i) {
      if (ExistEdge(index, i)) {
        --vertexs_[i].in_degree;
        --edges_total_num_;
      }
    }
    edges_.Remove(index);
    auto delete_elem = vertexs_[index];
    vertexs_.Remove(index);

    for (int i = 0; i < edges_.Size(); ++i) {
      if (ExistEdge(i, index)) {
        edges_[i][index].exist = false;
        --vertexs_[i].out_degree;
        --edges_total_num_;
      }
      edges_[i].Remove(index);
    }
    return delete_elem.data;
  }

  // for edge
  virtual const int& GetTotalEdgeSize() const { return edges_total_num_; }

  virtual bool ExistEdge(const int& i, const int& j) const {
    return (i >= 0 && i < vertexs_.Size() && j >= 0 && j < vertexs_.Size() &&
            edges_[i][j].exist);
  }

  virtual EdgeDataType& EdgeData(const int& i, const int& j) {
    return edges_[i][j].data;
  }

  virtual const EdgeDataType& EdgeData(const int& i, const int& j) const {
    return edges_[i][j].data;
  }

  virtual EdgeDataType& EdgeWeight(const int& i, const int& j) {
    return edges_[i][j].weight;
  }

  virtual const EdgeDataType& EdgeWeight(const int& i, const int& j) const {
    return edges_[i][j].weight;
  }

  virtual sstl::EdgeStatus& EdgeStatus(const int& i, const int& j) {
    return edges_[i][j].status;
  }

  virtual const sstl::EdgeStatus& EdgeStatus(const int& i,
                                                   const int& j) const {
    return edges_[i][j].status;
  }

  virtual void InsertEdge(const EdgeDataType& data, const int& weight,
                          const int& i, const int& j) {
    edges_[i][j].data = data;
    edges_[i][j].weight = weight;
    edges_[i][j].status = UNDETERMINED;
    edges_[i][j].exist = true;
    ++vertexs_[i].out_degree;
    ++vertexs_[j].in_degree;
    ++edges_total_num_;
  }

  virtual EdgeDataType RemoveEdge(const int& i, const int& j) {
    EdgeDataType edge_data = edges_[i][j].data;
    edges_[i][j].exist = false;
    --vertexs_[i].out_degree;
    --vertexs_[j].in_degree;
    --edges_total_num_;
    return edge_data;
  }

  void PrintAllVertex() const {
    std::cout << "vertex_size:" << GetTotalVertexSize() << std::endl;
    for (int i = 0; i < vertexs_.Size(); ++i) {
      vertexs_[i].PrintInfo();
      std::cout << std::endl;
    }
  }

  void PrintAllEdge(const char& mode) const {
    std::cout << "edge_size:" << GetTotalEdgeSize() << std::endl;
    int max_size = 1;
    if (mode == 'w') {
      int max = -1;
      for (int i = 0; i < edges_.Size(); ++i) {
        for (int j = 0; j < edges_.Size(); ++j) {
          if (EdgeWeight(i, j) > max) {
            max = EdgeWeight(i, j);
          }
        }
      }
      max_size = GetNumSize(max);
    }
    for (int i = 0; i < edges_.Size(); ++i) {
      for (int j = 0; j < edges_.Size(); ++j) {
        edges_[i][j].PrintInfo(mode);
        if (mode == 'w') {
          int now_size = GetNumSize(EdgeWeight(i, j));
          for (int i = now_size; i < max_size; ++i) {
            std::cout << " ";
          }
        }
        std::cout << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  static int GetNumSize(const int& num) {
    int the_num = num;
    int size = 1;
    while (the_num >= 10) {
      the_num /= 10;
      ++size;
    }
    return size;
  }

 private:
  int edges_total_num_;
  Vector<Vertex<VertexDataType>> vertexs_;
  Vector<Vector<Edge<EdgeDataType>>> edges_;
};
}  // namespace sstl
