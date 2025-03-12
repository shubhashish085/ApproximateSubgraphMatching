
#include "ApproximationAlgorithm.h"
#include "types.h"

void ApproximationAlgorithm::EWSample(const Graph *graph, float probability){

    size_t approx_triangle_count = 0;
    std::vector<std::pair<VertexID, VertexID>> sampled_edges;

    VertexID* neighbors;
    ui neighbor_count, sampled_edge_count = 0;
    VertexID random_vtx, u, w;

    for (const auto &edge_key: graph->edge_map){
        if(Util::isEdgeSelectable(probability)){
            sampled_edges.push_back(std::make_pair(edge_key.first.first, edge_key.first.second));
            sampled_edge_count++;
        }
    }

    std::cout << "Sampled Edge Count : " << sampled_edge_count << std::endl;

    for (const auto &edge: sampled_edges){

        VertexID lower_degree_vertex, higher_degree_vertex;
        if(graph->getVertexDegree(edge.first) <= graph->getVertexDegree(edge.second)){
            lower_degree_vertex = edge.first;
            higher_degree_vertex = edge.second;
        }else{
            lower_degree_vertex = edge.second;
            higher_degree_vertex = edge.first;
        }

        neighbors = graph-> getVertexNeighbors(lower_degree_vertex, neighbor_count);

        if(neighbor_count < 2){
            continue;
        }

        random_vtx = Util::randomlySelectedEdge(neighbors, neighbor_count, higher_degree_vertex);

        if(higher_degree_vertex < random_vtx){
            u = higher_degree_vertex;
            w = random_vtx;
        }else {
            u = random_vtx;
            w = higher_degree_vertex;
        }

        if(graph->edge_map.find(std::make_pair(u, w)) != graph->edge_map.end()){
            approx_triangle_count = approx_triangle_count + graph->getVertexDegree(lower_degree_vertex) - 1;
        }       

    }
    
    approx_triangle_count = (ui)(approx_triangle_count /(float) (3 * probability));

    std::cout << "Approximate Triangle Count with Probability : " << probability << " - " << approx_triangle_count << std::endl;
}


void ApproximationAlgorithm::count_triangles(const Graph *graph){

    std::cout << "Approximation Algorithm" << std::endl;
}