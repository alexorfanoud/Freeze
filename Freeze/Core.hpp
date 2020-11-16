#include "pch.hpp"
//Linux Platform
#include <signal.h>
#define ASSERT(x, ... ) if( !(x) ) {PrintArgs("[ASSERT ERROR: ", ##__VA_ARGS__, "]\n", __FUNCTION__, '\n', __FILE__, ": ", __LINE__); raise(SIGTRAP);}
//-------------------------//
template<typename ... Args >
void PrintArgs(Args&&... args){
    (std::cout << ... << args ) << std::endl;
}
