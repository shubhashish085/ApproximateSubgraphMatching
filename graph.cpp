#include "graph.h"
#include <fstream>
#include <algorithm>
#include <sstream>

void Graph::loadGraphFromFile(const std::string &file_path) {

    std::ifstream infile(file_path);

    if (!infile.is_open()) {
        std::cout << "Can not open the graph file " << file_path << " ." << std::endl;
        exit(-1);
    }

    char type;
    std::string input_line;
    ui label = 0;

    std::cout << "Reading File............ " << std::endl;

    ui line_count = 0, count = 0, comment_line_count = 4;

    while (std::getline(infile, input_line)) {

        //std::cout << " Input Line : " << input_line << std::endl;

        if (input_line.rfind("#", 0) == 0) {

            line_count++;

            if (input_line.rfind("# Nodes", 0) == 0) {
                std::stringstream ss(input_line);
                std::string token;
                int count = 0;
                while (!ss.eof()) {
                    std::getline(ss, token, ' ');
                    if (!(token.rfind("#", 0) == 0 || token.rfind("Nodes:", 0) == 0 || token.rfind("Edges:", 0) == 0)) {
                        if (count == 0) {
                            vertices_count = stoi(token);
                            degrees = new ui[vertices_count];
                            std::fill(degrees, degrees + vertices_count, 0);
        
                            count = 1;
                        } else {
                            edges_count = stoi(token);
                            count = 0;
                        }
                        
                    }
                }
            }
        }

        if(line_count >= comment_line_count){
            break;
        }
    }

    std::cout << "Vertices Count : " << vertices_count << " Edges Count : " << edges_count
                                  << std::endl;

    VertexID begin, end;


    while(infile >> begin) {

        infile >> end;

        if (begin != end && begin < vertices_count && end < vertices_count) {
            degrees[begin] += 1;
            degrees[end] += 1;
        }
    }

    infile.close();

    std::ifstream input_file(file_path);

    offsets = new ui[vertices_count +  1];
    offsets[0] = 0;

    neighbors = new VertexID[edges_count * 2];
    max_degree = 0;

    LabelID max_label_id = 0, begin_vtx_label, end_vtx_label;
    std::vector<ui> neighbors_offset(vertices_count, 0);// used for adjust neighbors with offset

    for(ui id = 0; id < vertices_count; id++){
        offsets[id + 1] = offsets[id] + degrees[id];

        if (degrees[id] > max_degree) {
            max_degree = degrees[id];
        }
    }

    line_count = 0;

    while (std::getline(input_file, input_line)) {
        line_count++;
        if(line_count >= comment_line_count){
            break;
        }
    }

    std::cout << "Comment Skipped !!!" << std::endl;

    while(input_file >> begin){ // Read edge.

        input_file >> end;

        line_count++;
        if(begin >= vertices_count || end >= vertices_count || begin == end){
            continue;
        }

        ui offset = offsets[begin] + neighbors_offset[begin]; // adjusting the index of neighbor in neighbors array
        neighbors[offset] = end;

        offset = offsets[end] + neighbors_offset[end]; // adjusting the index of neighbor in neighbors array
        neighbors[offset] = begin;

        if(begin < end){
            edge_map[std::make_pair(begin, end)] = true;
            edges.push_back(std::make_pair(begin, end));
        }else{
            edge_map[std::make_pair(end, begin)] = true;
            edges.push_back(std::make_pair(end, begin));
        }

        neighbors_offset[begin] += 1;
        neighbors_offset[end] += 1;
    }

    input_file.close();

    std::cout << "CSR Done !!!" << std::endl;

    for (ui i = 0; i < vertices_count; ++i) {
        std::sort(neighbors + offsets[i], neighbors + offsets[i + 1]); // sorting the neighbors of every vertex
    }
}


void Graph::loadGraphFromFileWithReindexing(const std::string& file_path){

    std::ifstream infile(file_path);

    if (!infile.is_open()) {
        std::cout << "Can not open the graph file " << file_path << " ." << std::endl;
        exit(-1);
    }

    char type;
    std::string input_line;
    ui label = 0;

    std::cout << "Reading File With Reindexing : " << file_path << std::endl;

    ui line_count = 0, count = 0, comment_line_count = 4;

    while (std::getline(infile, input_line)) {

        if (input_line.rfind("#", 0) == 0) {

            line_count++;

            if (input_line.rfind("# Nodes", 0) == 0) {
                std::stringstream ss(input_line);
                std::string token;
                int count = 0;
                while (!ss.eof()) {
                    std::getline(ss, token, ' ');
                    if (!(token.rfind("#", 0) == 0 || token.rfind("Nodes:", 0) == 0 || token.rfind("Edges:", 0) == 0)) {
                        if (count == 0) {
                            vertices_count = stoi(token);
                            count = 1;
                        } else {
                            count = 0;
                        }
                    }
                }
            }
        }

        if(line_count >= comment_line_count){
            break;
        }
    }

    std::cout << "Vertices Count : " << vertices_count << " Edges Count : " << edges_count << std::endl;

    degrees = new ui[vertices_count];
    std::fill(degrees, degrees + vertices_count, 0);

    idx_array = new ui[vertices_count];
    VertexID begin, end, tmp_vtx_idx = 0, offset;

    edges_count = 0;

    while(infile >> begin) {

        infile >> end;

        if(vtx_map_after_partition.find(begin) == vtx_map_after_partition.end()){

            vtx_map_after_partition[begin] = tmp_vtx_idx;
            idx_array[tmp_vtx_idx] = begin;
            tmp_vtx_idx++;
        }

        if(vtx_map_after_partition.find(end) == vtx_map_after_partition.end()){
            
            vtx_map_after_partition[end] = tmp_vtx_idx;
            idx_array[tmp_vtx_idx] = end;
            tmp_vtx_idx++;            
        }
        
        degrees[vtx_map_after_partition[begin]] += 1;
        degrees[vtx_map_after_partition[end]] += 1;
        edges_count++;        
    }

    infile.close();

    std::ifstream input_file(file_path);

    offsets = new ui[vertices_count +  1];
    offsets[0] = 0;

    neighbors = new VertexID[edges_count * 2];
    max_degree = 0;

    std::cout << "Vertices Count : " << vertices_count << " Edges Count : " << edges_count << std::endl;

    std::cout << "Initialization Finished.... " << std::endl;

    LabelID max_label_id = 0, begin_vtx_label, end_vtx_label;
    std::vector<ui> neighbors_offset(vertices_count, 0);// used for adjust neighbors with offset

    for(ui id = 0; id < vertices_count; id++){
        offsets[id + 1] = offsets[id] + degrees[id];

        if (degrees[id] > max_degree) {
            max_degree = degrees[id];
        }
    }

    line_count = 0;

    while (std::getline(input_file, input_line)) {
        line_count++;
        if(line_count >= comment_line_count){
            break;
        }
    }

    while(input_file >> begin){ // Read edge.

        input_file >> end;

        offset = offsets[vtx_map_after_partition[begin]] + neighbors_offset[vtx_map_after_partition[begin]]; // adjusting the index of neighbor in neighbors array
        neighbors[offset] = vtx_map_after_partition[end];

        offset = offsets[vtx_map_after_partition[end]] + neighbors_offset[vtx_map_after_partition[end]]; // adjusting the index of neighbor in neighbors array
        neighbors[offset] = vtx_map_after_partition[begin];

        neighbors_offset[vtx_map_after_partition[begin]] += 1;
        neighbors_offset[vtx_map_after_partition[end]] += 1;

        if(vtx_map_after_partition[begin] < vtx_map_after_partition[end]){
            edge_map[std::make_pair(vtx_map_after_partition[begin], vtx_map_after_partition[end])] = true;
            edges.push_back(std::make_pair(vtx_map_after_partition[begin], vtx_map_after_partition[end]));
        }else{
            edge_map[std::make_pair(vtx_map_after_partition[end], vtx_map_after_partition[begin])] = true;
            edges.push_back(std::make_pair(vtx_map_after_partition[end], vtx_map_after_partition[begin]));
        }
    }

    input_file.close();

    for (ui i = 0; i < vertices_count; ++i) {
        std::sort(neighbors + offsets[i], neighbors + offsets[i + 1]); // sorting the neighbors of every vertex
    }
}

