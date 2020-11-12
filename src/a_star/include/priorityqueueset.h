#ifndef PRIORITYQUEUESET_H
#define PRIORITYQUEUESET_H

#include<set>
#include <iostream>
#include <algorithm>
#include <functional>

template <typename T,typename cmp=std::less<>>
class priorityQueueSet{
public:
    std::set<T> elements;
    void push(T t){elements.insert(t);}
    auto begin(){return elements.begin();}
    //cmp comparator;
    T test;
    auto end(){return elements.end();}
    T pop(cmp comparator={});
 
    priorityQueueSet(){};
    bool empty(){return elements.size()==0;}

    
};

template <typename T,typename cmp>
T priorityQueueSet<T,cmp>::pop(cmp comparator)
{

    auto result=std::min_element(elements.begin(),elements.end(),comparator);
    elements.erase(result);
    return *result;

}

#endif // PRIORITYQUEUESET_H
