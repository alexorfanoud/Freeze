#include <signal.h>
#define ASSERT(x) if( !(x) ) raise(SIGTRAP) 