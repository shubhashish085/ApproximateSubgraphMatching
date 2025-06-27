#include "util.h"
#include <random>
#include <unordered_set>

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

ui Util::exact_neighbor_intersection(const Graph* data_graph, VertexID& u, VertexID& w){

  ui common = 0, u_nbr_cnt = 0, w_nbr_cnt = 0;

	VertexID* u_neighbors = data_graph->getVertexNeighbors(u, u_nbr_cnt);
	VertexID* w_neighbors = data_graph->getVertexNeighbors(w, w_nbr_cnt);

	std::unordered_set <VertexID> set;

	for (int i = 0; i < u_nbr_cnt; i++) set.insert(u_neighbors[i]);
	for (int j = 0; j < w_nbr_cnt; j++) {
		if (set.find(w_neighbors[j]) != set.end()){
        common++;
    }
	}
	return common;
}