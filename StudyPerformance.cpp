
#include <cmath>
#include <mpi.h>
#include "graph.h"
#include "types.h"
#include "ApproximationAlgorithm.h"




int main(int argc, char** argv){

    std::string input_data_graph_file = "/home/kars1/Research_Projects/metis/2_livejournal_0.graph";

    Graph* data_graph = new Graph();
    data_graph->loadGraphFromFile(input_data_graph_file);

    float probability = 0.1;

    while (probability <= 1.00){
        ApproximationAlgorithm::EWSample_square(data_graph, probability);
        probability += 0.1;
    }    

}


/*
//Test Run
int main(int argc, char** argv){

    std::string input_data_graph_file = "/home/kars1/Research_Projects/metis/2_amazon_1.graph";

    Graph* data_graph = new Graph();
    data_graph->loadGraphFromFileWithReindexing(input_data_graph_file);

    float probability = 0.1;

    while (probability <= 1.00){
        ApproximationAlgorithm::EWSample(data_graph, probability);
        probability += 0.1;
    }    

}*/


/*int main(int argc, char** argv){

    std::string input_data_graph_file = "/home/kars1/Research_Projects/metis/2_amazon_partition.graph";
    std::string original_data_graph_file = "/home/kars1/Parallel_computation/dataset/com-amazon.ungraph.txt";

    Graph* data_graph = new Graph();
    //data_graph->loadGraphFromFileWithReindexing(input_data_graph_file);
    data_graph -> loadGraphWithPartitionedEdgesFromFile(input_data_graph_file, original_data_graph_file);


    float probability = 0.1;

    while (probability <= 1.00){
        ApproximationAlgorithm::EWSampleForPartitionEdges(data_graph, probability);
        probability += 0.1;
    }    

}*/


/*int main(int argc, char** argv){

    std::string input_data_graph_file_prefix = "/home/kars1/Research_Projects/metis/", input_data_graph_file;
    std::string original_data_graph_file = "/home/kars1/Parallel_computation/dataset/com-amazon.ungraph.txt";

    ui numberOfPartitions = 2;
    std::string dataset_prefix = "amazon";
    float probability = 0.1;

    ui approx_embedding_count = 0;
    ui exact_embedding_count = 150613;

    ui* process_wise_embedding_count;

    int world_process_cnt, world_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &world_process_cnt);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    if(world_rank == 0){

        input_data_graph_file = input_data_graph_file_prefix + std::to_string(numberOfPartitions) + "_" + dataset_prefix + "_partition.graph";

        process_wise_embedding_count = new ui[world_process_cnt];

        Graph *data_graph = new Graph();
        data_graph -> loadGraphWithPartitionedEdgesFromFile(input_data_graph_file, original_data_graph_file);

        ui prc_approx_embedding_count = ApproximationAlgorithm::EWSampleForPartitionEdges(data_graph, probability);

        ui other_prc_approx_embedding_count;

        MPI_Status status;

        for(ui i = 1; i < world_process_cnt; i++){

            MPI_Recv(&other_prc_approx_embedding_count, 1, MPI_UNSIGNED, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            process_wise_embedding_count[i] = other_prc_approx_embedding_count;
        }

        process_wise_embedding_count[0] = prc_approx_embedding_count;

        for(ui i = 0; i < world_process_cnt; i++){
            approx_embedding_count += process_wise_embedding_count[i];
        }

        float absolute_error = (float)(std::fabs(exact_embedding_count - approx_embedding_count) * 100.0) / (float)(exact_embedding_count);
        std::cout << "Total Approximate Embedding count : " << approx_embedding_count << std::endl;
        std::cout << "Absolute Error : " << (float)(std::fabs(exact_embedding_count - approx_embedding_count))  << std::endl;
        std::cout << "Absolute Error : " << (float)(std::fabs(exact_embedding_count - approx_embedding_count)) * 100.0 / exact_embedding_count << std::endl;


    }else {
        ui file_idx = world_rank - 1;        
        input_data_graph_file = input_data_graph_file_prefix + std::to_string(numberOfPartitions) + "_" + dataset_prefix + + "_" + std::to_string(file_idx) + ".graph";

        Graph *data_graph = new Graph();
        data_graph -> loadGraphFromFileWithReindexing(input_data_graph_file);

        ui prc_approx_embedding_count = ApproximationAlgorithm::EWSample(data_graph, probability);

        MPI_Send(&prc_approx_embedding_count, 1, MPI_UNSIGNED, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();       

}*/