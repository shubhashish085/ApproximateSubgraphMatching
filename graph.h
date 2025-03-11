
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <map>
#include "types.h"

class Graph{

private:

    ui vertices_count;
    ui edges_count;
    ui max_degree;

    ui* degrees;
    ui* offsets;
    VertexID* neighbors;


public:

    Graph() {

        vertices_count = 0;
        edges_count = 0;
        max_degree = 0;

        offsets = NULL;
        neighbors = NULL;
    }

    ~Graph() {
        delete[] offsets;
        delete[] neighbors;
    }

public:
    void loadGraphFromFile(const std::string& file_path);
    void printGraphMetaData();

public:

    std::vector<std::pair<VertexID, VertexID>> edges;
    std::map<std::pair<VertexID,VertexID>, bool> edge_map;

    const ui* getOffsets() const {
        return offsets;
    }

    const ui getVerticesCount() const {
        return vertices_count;
    }

    const ui getEdgesCount() const {
        return edges_count;
    }

    const ui getVertexDegree(const VertexID id) const {
        return offsets[id + 1] - offsets[id];
    }

    const ui getGraphMaxDegree() const {
        return max_degree;
    }

    ui * getVertexNeighbors(const VertexID id, ui& count) const {
        count = offsets[id + 1] - offsets[id]; // used for neighbor count
        return neighbors + offsets[id];
    }

    void getNeighborCount(const VertexID id, ui& count) const {
        count = offsets[id + 1] - offsets[id];
    }


    bool checkEdgeExistence(VertexID u, VertexID v) const {
        if (getVertexDegree(u) < getVertexDegree(v)) {
            std::swap(u, v);
        }
        ui count = 0;
        const VertexID* neighbors =  getVertexNeighbors(v, count);

        int begin = 0;
        int end = count - 1;
        while (begin <= end) {
            int mid = begin + ((end - begin) >> 1);
            if (neighbors[mid] == u) {
                return true;
            }
            else if (neighbors[mid] > u)
                end = mid - 1;
            else
                begin = mid + 1;
        }

        return false;
    }

    void printGraphData(){

        std::cout << " >>>>> Degree <<<<<<" << std::endl;

        for(ui i = 0; i < vertices_count; i++){
            std::cout << degrees[i] << " ";
        }

        std::cout << std::endl;

        std::cout << " >>>>> Offset <<<<<<" << std::endl;

        for(ui i = 0; i < vertices_count + 1; i++){
            std::cout << offsets[i] << " ";
        }

        std::cout << std::endl;

        std::cout << " >>>>> Neighbors <<<<<<" << std::endl;

        for(ui i = 0; i < edges_count; i++){
            std::cout << neighbors[i] << " ";
        }

        std::cout << std::endl;    
    }

};


#endif