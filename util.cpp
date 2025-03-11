#include "util.h"
#include <random>

bool Util::isEdgeSelectable (float probability) {
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  double randomValue = dis(gen);
  return randomValue <= probability;
}


VertexID Util::randomlySelectedEdge(VertexID*& neighbors, ui& neighbor_count, VertexID u){

    if(neighbor_count == 2){
      if(neighbors[0] == u){
        return neighbors[1];
      }else{
        return neighbors[0];
      }
    }

    ui selected_edge_idx;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    selected_edge_idx = (ui) (randomValue * neighbor_count);

    if(selected_edge_idx == neighbor_count){
      selected_edge_idx -= 1;
    }

    while(u == neighbors[selected_edge_idx]){

      randomValue = dis(gen);
      selected_edge_idx = (ui) (randomValue * neighbor_count);
      if(selected_edge_idx == neighbor_count){
        selected_edge_idx -= 1;
      }
    }

    return neighbors[selected_edge_idx];
}