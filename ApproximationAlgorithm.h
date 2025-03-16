#ifndef APPROXIMATIONALGORITHM_H
#define APPROXIMATIONALGORITHM_H

#include "graph.h"
#include "util.h"
#include <vector>
#include <utility>

class ApproximationAlgorithm {

public:
    static void count_triangles(const Graph *graph);
    static void EWSample(const Graph *graph, float probability);
    //static void distributedEWSample(const Graph *graph, float probability);
    static void EWSampleForPartitionEdges(const Graph *graph, float probability);
};

#endif