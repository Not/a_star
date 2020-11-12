#include <iostream>
#include "graph.h"
#include "point.h"
#include "priorityqueueset.h"
#include "a_star.h"
#include "node.h"
#include "debug.h"
#define PLOT

#ifdef PLOT
    #include <opencv2/imgproc/imgproc.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include "plot_nodes.h"
#endif

using namespace std;

int main()
{
    
    Graph graf;
    graf.loadFromFile(R"(graf.txt)",Graph::graph_representation::AdjMatrix);
    graf.computeDistances();
    DEBUG_MSG(graf);
    //graf.addNode(Node(Point(4,0),"new1"),{ {8,{1,1}},{9,{2,3}} });
    
    A_Star search(graf,A_Star::a_star_mode::full);
    search();
    auto path=search.create_path();
   
\
    for(auto el:path){
        cout<<el->name<<", ";
    }
    #ifdef PLOT
        auto plt=plot_nodes(&graf,150);
        plt.draw_path(path);
        plt.draw_nodes();
    #endif

    return 0;

}
