# simple stl
*this lib simplifies the achievement details of common container, but add the container variety*, the whole code partily follow the Google Style. </br>
Email: wujiazheng2020@gmail.com</br>
Notice: it follows the MIT license, you can use it almost anyway for free.
## why i do this?
i do this mainly for challenge, in fact, I finished it in 96 hours with 10800 code-lines, it made me very happy, the other reason is i want to prepare for a more interesting project, it may need some data structure.
## Code Structure
container <- algorithm <- application </br>
so, container is just at the bottom, it's quite simple
## Acknowledge
when i wrote this code , i refer to the DSA book of dengjunhui and << algorithm introduction >>, but I basically changed it completely, including the achievement and encapsulation, to make it easier to be used by engineering code. especially in the part of the "tree"</br>
i use std::vector just for produce prime_table and fibonacci table in complie time, because i think it's a good achievement
## Content
### 1.Container
* auxiliary_space
* bitmap
* vector
* list
* stack
* queue
* pair
* binary_tree
* binary_search_tree
* splay_tree
* avl_tree
* b_minus_tree
* red_black_tree
* set
* map
* graph
* string
* bucket
* graph
* huffman_forest
* hash_map
* unordered_set
* unordered_map
* complete_heap
* left_heap
* priority_queue

### 2. Algorithm
Includes following type </br>
* deduplicator (for unordered)
* uniquifier (for ordered)
* finder (for unordered)
* searcher (for ordered)
* partition
* reverser
* selector (for example: k_th select)
* sorter
* traverser
* matcher (for string)

## How To Build?
* **Update Cmake to 3.21.1 version(requirement)**
* install glog(just find in github)
* mkdir build
* cd build
* cmake ..
* make -j8
* make test</br>
**Notice:** I use fetchcontent to fetch Gtest in cmakelist, so, if you are in china, you should use VPN, or you can install gtest using source(just find in github).

## Requirement
* gtest
* **cmake(>=3.20)**
* glog
* lcov(if you need to see coverage)
