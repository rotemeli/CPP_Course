//
// Created by ELON HADAD on 19/01/2023.
//

#ifndef EX_05_GRAPH_H
#define EX_05_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <stdexcept>

using namespace std;

class Graph {

private:
    vector<vector<int> > adj_matrix;
    map<string, int> vertex_map;
    map<int, string> reverse_map;
    int num_vertices;

public:
    Graph() : num_vertices(0) {};

    Graph(const Graph &g);

    Graph &operator=(const Graph &g);

    virtual ~Graph();

    void add_vertex(const string &vertex);

    void delete_vertex(const string &vertex);

    void add_edge(const string &start, const string &end, int weight);

    void delete_edge(const string &start, const string &end);

    void update_edge_weight(const string &start, const string &end, int newWeight);

    int get_edge_weight(const string &start, const string &end);

    vector<string> get_neighbors(const string &vertex);

    vector<string> get_connected(const string &vertex);

    int getNumVertices() const;

    void printGraph(const string &vertex);

    void printGraph(ofstream &file);

};


#endif //EX_05_GRAPH_H