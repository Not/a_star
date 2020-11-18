#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <sstream>
#include <vector>
#include "node.h"
#include <string>
#include <fstream>
#include <map>


class Graph
{

public:
    enum graph_representation{
        AdjMatrix,
        AdjList,
    };
    enum norm{
        Euler,
        Zero
    };


    explicit Graph();
    size_t size();
    void loadFromFile(std::string filename,graph_representation rep);
    void computeDistances(norm Norm=norm::Euler);
    friend const std::ostream& operator<<(std::ostream&, const Graph&);
    void addNode(Node n,std::map<size_t,std::pair<double,double>> weights);
    std::vector<Node> nodes;
    Node* startNode,*endNode;

};

#endif // GRAPH_H
