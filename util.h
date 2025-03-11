#ifndef UTIL_H
#define UTIL_H

#include "graph.h"


class Util {
public:
    static bool isEdgeSelectable(float probability);
    static VertexID randomlySelectedEdge(VertexID*& neighbors, ui& neighbor_count, VertexID u);   
};


#endif


