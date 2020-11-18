#include "graph.h"
#include <fstream>
#include <string>
#include <regex>
#include "point.h"
#include <map>
#define DEBUG
#include "debug.h"

Graph::Graph()
{


}
size_t Graph::size(){
    return nodes.size();
}

void Graph::loadFromFile(std::string filename, Graph::graph_representation rep)
{
    std::ifstream file;
    std::ofstream f;
    f.open("g.txt");
    f<<"Gf";
    f.close();
   
    std::string nodes_description;

    file.clear();
    file.open(filename);


    if(file.is_open()){
        //Użycie wyrażeń regularnych do wyszukiwania współrzędnych punktów w formacie:
        //(1.2 3) (4.312 435)... 
         //std::regex re( R"regex(\(([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?+), ?([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?+)\))regex");
         std::regex re( R"regex(\((.*?),(.*?)\))regex");

         getline(file,nodes_description);
         std::smatch  matches;
         while(std::regex_search(nodes_description,matches,re)){
             auto x=std::stod(matches.str(1));
             auto y=std::stod(matches.str(2));
             nodes.push_back(Node(Point(x,y))); //zapełnienie wektora nowymi węxłami
             nodes_description=matches.suffix().str(); //usunięcie dodanego węzła z tekstu
         }
         size_t s,e; file >> s>>e;  //indeksy pierwszego i ostatniego węzła

         startNode=&nodes.at(s-1);
         startNode->g=0;
         endNode=&nodes.at(e-1); //przypisanie wskaźników do końcowych węzłow

         switch(rep){ //sposób reprezentacji krawędzi w pliku
         case graph_representation::AdjMatrix: //na razie tylko macierz sąsiedztwa
             for(size_t i=0;i<size();i++){
                 for(size_t j=0;j<size();j++){
                     double weight;
                     file>>weight; //wczytanie wagi
                     if(weight>0) nodes.at(i).connect(&nodes.at(j),weight); //utworzenie połączenia między danymi węzłami
                     if(!file){
                         std::cerr<<"ERROR - edges representation not correct";
                     }

                 }
             }

             break;
         default:
             std::cerr<<"ERROR - such representation do not exist";

         }
    }
    else{
        DEBUG_MSG("ERROR file open: "<<file.rdstate());
        exit(1);

    }
}

void Graph::computeDistances(norm Norm)
{

    for(auto &n:nodes){
        switch(Norm){
            case norm::Euler:
                n.distance=n.coordinates.getDistance(endNode->coordinates);
            break;
            case norm::Zero:
                n.distance=0;
            break;
        }
    }

}

const std::ostream& operator<<(std::ostream& stream, const Graph& g) {
       stream<<"Graph{size:"<<g.nodes.size()<<", startNode:"<<g.startNode->name<<", endNode: "<<g.endNode->name<<", nodes:["<<std::endl;
       for(auto n:g.nodes){
           stream<<'\t'<<n<<std::endl;
       }
       stream<<"]}";
       return stream;
}

void Graph::addNode(Node n,std::map<size_t,std::pair<double,double>> weights){
    //mapa zawiera klucz- index wezla w grafie oraz 2 wartosci - wagę połączenia z nowego węzła oraz do niego
                                                                             
    nodes.push_back(n);
    for(auto connection:weights){
        nodes.back().connect(&nodes.at(connection.first), connection.second.first/*waga z węzła */); 
        nodes.at(connection.first).connect(&nodes.back(),connection.second.second);
    }

}


