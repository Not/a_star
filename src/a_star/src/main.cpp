#include <iostream>
#include "graph.h"
#include "point.h"
#include "priorityqueueset.h"
#include "a_star.h"
#include "node.h"


#define PLOT

#ifdef PLOT
    #include <opencv2/imgproc/imgproc.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include "plot_nodes.h"
#endif

#define DEBUG //Wypisywanie wszystkich informacji
#include "debug.h"

using namespace std;

int main(int argc, char**argv)
{
   
   string filename=R"(graf.txt)";

    if(argc<2){
        DEBUG_MSG("Waring, filename not provided, assumed 'graf.txt'"<<std::endl);
    }
    else{
        filename=argv[1];
        DEBUG_MSG(filename);
    }

    Graph graf;
    graf.loadFromFile(filename,Graph::graph_representation::AdjMatrix); //wczytanie struktury grafu, położeń węzłów oraz krawędzi. Można wybrać sposób zapisu danych (TODO)
   
    //graf.addNode(Node(Point(4,0),"new1"),{ {8,{1,1}},{9,{2,3}} }); //dodawanie kolejnych wezłów w razie potrzeby
    //należy podać węzeł oraz listę zawierającą połączenia z innymi węzłami na podstawie indeksów oraz 2x double:  wagę połączenia z nowego węzła oraz do niego
  
    //Utworzenie obiektu przeszukiwania
    A_Star search(graf,A_Star::a_star_mode::full);
    //do wyboru tryb full, simple oraz dijkstra
     DEBUG_MSG(graf);
    //Uruchomienie algorytmu:
    if(!search()) return -1;

    //Wyliczenie ścieżki start -> end:
    auto path=search.create_path();
   
   //wypisanie wyniku:
    bool first=true;
    for(auto el:path){
        if (!first) std::cout<<", ";
        first=false;
        //std::cout<<el->name; //wypisanie wyniku jako nazwy
        std::cout<<el->index; //wypisanie wyniku jako indeksy
    }

    //narysowanie grafu (wymaga opencv):
    #ifdef PLOT
        auto plt=plot_nodes(&graf,150);
        plt.draw_path(path);
        plt.draw_nodes();
    #endif

    return 0;

}
