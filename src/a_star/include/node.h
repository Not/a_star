#ifndef NODE_H
#define NODE_H
#include "point.h"
#include <vector>
#include <string>
#include <utility>
#include <limits>





class Node
{
public:
    static int nodeCount;
    double distance=0;
    double g=std::numeric_limits<double>::infinity();
    Node(Point pt,std::string name=std::string(1,static_cast<char>(nodeCount)+'A'));
    Point coordinates;
    std::string name;
    size_t index;
    friend std::ostream& operator<<(std::ostream&, const Node&);
    void connect( Node*, double weight);
    std::vector<std::pair< Node*,double>> edges;

   

};

#endif // NODE_H
