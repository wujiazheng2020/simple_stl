/*
 * Copyright 2021 Jiazheng Wu
 *
 * FileName: prim_mst.h
 *
 * Author: Jiazheng Wu
 * Email: wujiazheng2020@gmail.com
 * Licensed under the MIT License
 */

#pragma once

#include "simple_stl/algorithm/graph_algorithm/traverser/pfs_traverser.h"
#include "simple_stl/application/graph_application/min_span_tree_related/prim_mst/prim_end_function.h"
#include "simple_stl/application/graph_application/min_span_tree_related/prim_mst/prim_initializer.h"
#include "simple_stl/application/graph_application/min_span_tree_related/prim_mst/prim_prior_selector.h"
#include "simple_stl/application/graph_application/min_span_tree_related/prim_mst/prim_prior_updater.h"

namespace sstl {
// prior is the path size
// we choose the shortest path one which is the lowest prior one
// prim for construct minimum spanning tree
// time complexity: O(n^2)
// if you use prim for all connected field,
// then we can get a union-find sets algorithm
// for each child just i = i->parent , it can backtrace to a solo root
// mainly for undirected graph
class PrimMST : public PFSTraverser<PrimInitializer, PrimPriorUpdater,
                                    PrimPriorSelector, PrimEndFunction> {};
}  // namespace sstl
