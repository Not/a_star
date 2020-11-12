#include "a_star.h"
#include "priorityqueueset.h"
#include "debug.h"

A_Star::A_Star(Graph &g,a_star_mode mode_):graf(g),thru(g.size(),-1),mode(mode_)
{

}

void A_Star::operator()()
{
   if(mode==a_star_mode::simple) DEBUG_MSG("Simple"<<std::endl);
   if(mode==a_star_mode::full) DEBUG_MSG("FULL");
   queue.push(graf.startNode);
   int i=1;
   
   while(!queue.empty()){
       DEBUG_MSG("{");
            for(auto el:queue) DEBUG_MSG(el->name<<"-");
       DEBUG_MSG("}");
       auto current_node=queue.pop();

       DEBUG_MSG("krok "<<i++<<" Jestem w node "<<current_node->name<<std::endl);


       if(current_node==graf.endNode){
           DEBUG_MSG("END");
           return;
       }
       visited.insert(current_node);
       
       for(auto &neighbour:current_node->edges){
           if(visited.count(neighbour.first) && mode==a_star_mode::simple){
               continue;
           }
           auto g=current_node->g+neighbour.second;
           
            DEBUG_MSG('\t'<<"sprawdzam node "<<neighbour.first->name<<" g="<<g<<std::endl);
           
           if(neighbour.first->g>g){
               neighbour.first->g=g;
               thru.at(neighbour.first->index)=current_node->index;//
               DEBUG_MSG("\t\t"<<"Updated "<<neighbour.first->name<<std::endl);
               queue.push(neighbour.first);


           }
       }
   }
   DEBUG_MSG("FAIL?");
}
std::list<Node*> A_Star::create_path(){
    auto index=graf.endNode->index;
    auto result=std::list<Node*>();
    result.push_front(graf.endNode);
    while(index!=graf.startNode->index){
        index=thru.at(index);
        result.push_front(&graf.nodes.at(index));
    }
    return result;
    
}

//std::function<bool(const Node*,const Node*)> A_Star::cmp= [](const Node* n1,const Node* n2){
//       return (n1->distance>n2->distance);
//   };
