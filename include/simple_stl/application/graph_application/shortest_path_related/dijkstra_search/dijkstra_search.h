/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: dijkstra_search.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/graph_algorithm/traverser/pfs_traverser.h"
#include "simple_stl/application/graph_application/shortest_path_related/dijkstra_search/dijkstra_end_function.h"
#include "simple_stl/application/graph_application/shortest_path_related/dijkstra_search/dijkstra_initializer.h"
#include "simple_stl/application/graph_application/shortest_path_related/dijkstra_search/dijkstra_prior_selector.h"
#include "simple_stl/application/graph_application/shortest_path_related/dijkstra_search/dijkstra_prior_updater.h"

namespace sstl {
// prior is the path size
// we choose the shortest path one which is the lowest prior one
// find shortest path from start_index to end_index
// time complexity: O(n^2)
class DijkstraSearch
    : public PFSTraverser<DijkstraInitializer, DijkstraPriorUpdater,
                          DijkstraPriorSelector, DijkstraEndFunction> {};
}  // namespace sstl
