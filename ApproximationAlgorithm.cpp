
#include "ApproximationAlgorithm.h"
#include "types.h"
#include <vector>

ui ApproximationAlgorithm::EWSample(const Graph *graph, float probability){

    ui approx_triangle_count = 0;
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

    return approx_triangle_count;
}


ui ApproximationAlgorithm::EWSampleForPartitionEdges(const Graph *graph, float probability){

    ui approx_triangle_count = 0;
    std::vector<std::pair<VertexID, VertexID>> sampled_edges;

    VertexID* neighbors;
    ui neighbor_count, sampled_edge_count = 0, wedge_count = 0;
    VertexID random_vtx, v, w, edge_start_vtx, edge_end_vtx;

    for (const auto &edge_key: graph->edge_map){
        if(Util::isEdgeSelectable(probability)){
            sampled_edges.push_back(std::make_pair(edge_key.first.first, edge_key.first.second));
            sampled_edge_count++;
        }
    }

    std::cout << "Sampled Edge Count From Partition : " << sampled_edge_count << std::endl;
    std::cout << "Full Graph Edge Size : " << graph->full_graph_edge_map.size() << std::endl;

    for (const auto &edge: sampled_edges){

        VertexID lower_degree_vertex, higher_degree_vertex;
        neighbor_count = 0;

        if(graph->getVertexDegree(edge.first) <= graph->getVertexDegree(edge.second)){
            lower_degree_vertex = edge.first;
            higher_degree_vertex = edge.second;
        }else{
            lower_degree_vertex = edge.second;
            higher_degree_vertex = edge.first;
        }

        neighbors = graph-> getVertexNeighbors(higher_degree_vertex, neighbor_count);

        if(neighbor_count < 2){
            continue;
        }

        wedge_count++;

        random_vtx = Util::randomlySelectedEdge(neighbors, neighbor_count, lower_degree_vertex);

        if(lower_degree_vertex < random_vtx){
            v = lower_degree_vertex;
            w = random_vtx;
        }else {
            v = random_vtx;
            w = lower_degree_vertex;
        }

        //std::cout << "Wedge No " << wedge_count << " : " << higher_degree_vertex << ", " << v << ", " << w << std::endl;

        if(graph->idx_array[v] < graph->idx_array[w]){
            edge_start_vtx = graph->idx_array[v];
            edge_end_vtx = graph->idx_array[w];

        }else{
            edge_start_vtx = graph->idx_array[w];
            edge_end_vtx = graph->idx_array[v];
        }


        if(graph->full_graph_edge_map.find(std::make_pair(edge_start_vtx, edge_end_vtx)) != graph->full_graph_edge_map.end()){
            approx_triangle_count = approx_triangle_count + graph->getVertexDegree(higher_degree_vertex) - 1;
        }       

    }
    
    approx_triangle_count = (ui)(approx_triangle_count /(float) (3 * probability));

    std::cout << "Approximate Triangle Count with Probability - " << probability << " : " << approx_triangle_count << std::endl;

    return approx_triangle_count;
}




void ApproximationAlgorithm::count_triangles(const Graph *graph){

    std::cout << "Approximation Algorithm" << std::endl;
}