#include "a_star.h"
#include "priorityqueueset.h"
#include "debug.h"

A_Star::A_Star(Graph &g,a_star_mode mode_):graf(g),thru(g.size(),-1),mode(mode_)
{
    if(mode==a_star_mode::full || mode ==a_star_mode::simple){
        g.computeDistances(Graph::norm::Euler);
    }
    else{
        g.computeDistances(Graph::norm::Zero);
    }
    

}

void A_Star::operator()()
{
   if(mode==a_star_mode::simple) DEBUG_MSG("Simple"<<std::endl);
   if(mode==a_star_mode::full) DEBUG_MSG("FULL");
   queue.push(graf.startNode);
   int i=1;
   
   while(!queue.empty()){
       DEBUG_MSG("{");
            for(auto el:queue) DEBUG_MSG(el->name<<"-"); //wypisanie stanu kolejki
       DEBUG_MSG("}");
       auto current_node=queue.pop(); //wyjecie elementu

       DEBUG_MSG("krok "<<i++<<" Jestem w node "<<current_node->name<<std::endl);


       if(current_node==graf.endNode){ //jeśli koniec to koniec
           DEBUG_MSG("END");
           return;
       }
       visited.insert(current_node); //dodanie do listy odwiedzonych, w full niepotrzebne ale co mi tam
       
       for(auto &neighbour:current_node->edges){
           if(visited.count(neighbour.first) && mode==a_star_mode::simple){ //jeśli tryb prosty to omijamy odwiedzone
               continue;
           }
           auto g=current_node->g+neighbour.second; //tymczasowe g;
           
            DEBUG_MSG('\t'<<"sprawdzam node "<<neighbour.first->name<<" g="<<g<<std::endl);
           
           if(neighbour.first->g>g){ //aktualizacja g
               neighbour.first->g=g; 
               thru.at(neighbour.first->index)=current_node->index;//
               DEBUG_MSG("\t\t"<<"Updated "<<neighbour.first->name<<std::endl);
               queue.push(neighbour.first);
           }
       }
   }
   DEBUG_MSG("FAIL?");
}
std::list<Node*> A_Star::create_path(){ //odtworzenie drogi na podstawie wektora thru
    auto index=graf.endNode->index;
    auto result=std::list<Node*>();
    result.push_front(graf.endNode);
    while(index!=graf.startNode->index){
        index=thru.at(index);
        result.push_front(&graf.nodes.at(index));
    }
    return result;
    
}

