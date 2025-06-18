#ifndef DEBUG_H
#define DEBUG_H

#if DO_DEBUG == 1
    #define DEBUG(X) X
    #define NO_DEBUG(X)
#else
    #define DEBUG(X)
    #define NO_DEBUG(X) X
#endif

#endif //DEBUG_H
