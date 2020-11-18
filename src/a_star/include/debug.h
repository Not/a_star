#ifndef DEBUG_H
#define DEBUG_H



    //#define DEBUG
    #ifdef DEBUG
    #define DEBUG_MSG(str) std::cout << str
    #else
    #define DEBUG_MSG(str) 0;
    #endif


#endif