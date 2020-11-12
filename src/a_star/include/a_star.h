#ifndef A_STAR_H
#define A_STAR_H
#include "graph.h"
#include <queue>
#include <functional>
#include "priorityqueueset.h"
#include <list>
#include <set>


class A_Star
{
public:
    enum a_star_mode{
        full,
        simple,
        dijkstra
    }mode;
    int test;
    A_Star(Graph &g,a_star_mode mode=a_star_mode::full);
    void operator()();
    std::list<Node*> create_path();
private:
    Graph &graf;


    struct cmp{
        bool operator()(const Node* n1,const Node* n2){
            //if (mode==a_star_mode::dijkstra){zrób coś}
            return (n1->distance+n1->g < n2->distance+n2->g);
        }
    };    
    


    //static std::function<bool(const Node*,const Node*)> cmp;
    //std::priority_queue< const Node*,std::vector<const Node*>,decltype(cmp)> queue{cmp};

    priorityQueueSet<Node*,cmp> queue;
    std::vector<int> thru;
    std::list<Node*> path;
    std::set<Node*> visited;

};

#endif // A_STAR_H