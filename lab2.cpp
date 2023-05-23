#include "lab2.h"

//
// lab2 code should be located here!
//


unsigned int lab2_thread_graph_id() 
{
    return 999;
}

const char* lab2_unsynchronized_threads()
{
    return "xyz";
}

const char* lab2_sequential_threads()
{
    return "rst,tuvw";
}


int lab2_init()
{
    // ...
    
    pthread_create(...);
    // ...

    pthread_join(...);
    // ...
    
    return 0;
}
