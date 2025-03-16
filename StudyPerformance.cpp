#include "graph.h"
#include "types.h"
#include "ApproximationAlgorithm.h"


/*int main(int argc, char** argv){

    std::string input_data_graph_file = "/home/kars1/Research_Projects/metis/2_livejournal_0.graph";

    Graph* data_graph = new Graph();
    data_graph->loadGraphFromFile(input_data_graph_file);

    float probability = 0.1;

    while (probability <= 1.00){
        ApproximationAlgorithm::EWSample(data_graph, probability);
        probability += 0.1;
    }    

}*/


int main(int argc, char** argv){

    std::string input_data_graph_file = "/home/kars1/Research_Projects/metis/2_amazon_1.graph";

    Graph* data_graph = new Graph();
    data_graph->loadGraphFromFileWithReindexing(input_data_graph_file);

    float probability = 0.1;

    while (probability <= 1.00){
        ApproximationAlgorithm::EWSample(data_graph, probability);
        probability += 0.1;
    }    

}

