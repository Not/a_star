#include "node.h"
#include <ostream>
#include <utility>
#include <point.h>

Node::Node(Point pt,std::string nm):coordinates(pt),name(nm)
{
    index=nodeCount++;
}

void Node::connect( Node* n , double weight) //utworzenie krawędzi z innym węzłem
{
    edges.push_back(std::pair<Node*,double>(n,weight));

}
std::ostream& operator<<(std::ostream& stream, const Node& n) { //do cout<<node
        stream <<"node{name:"<<n.name<<",coord:"<<n.coordinates<<",dist:"<<n.distance<<",neighbours:[";
        bool first{true};
        for(auto &edge:n.edges){
            if(!first) stream<<",";
            first=false;
            stream<<edge.first->name<<"("<<edge.second<<")";
        }
        stream<<"]}";

        return stream;
}
int Node::nodeCount=0;
