#ifndef CASSIUS_SOURCE_CLUAENGINE_DEBUG_HPP
#define CASSIUS_SOURCE_CLUAENGINE_DEBUG_HPP

#ifndef NDEBUG

#include <iostream>


// used to run STATEMENT wrapped with a dumpStack pretty print.
//
// STATEMENT can be anything you can stick  ; after.
//
// example: WITH_STACKDUMP(do { ... } while(0));
//

#define WITH_STACKDUMP(statement) \
    std::cout << std::endl \
              << "pre-dumping stack" \
              << std::endl; \
    dumpStack(interp); \
    std::cout << "END OF PRE STACK DUMP" << std::endl; \
    \
    statement ; \
    \
    std::cout << std::endl \
              << "post-dumping stack" \
              << std::endl; \
    dumpStack(interp); \
    std::cout << "END OF MY STACK DUMP" << std::endl 
#else
#define WITH_STACKDUMP(statement) \
    statement
#endif

#endif

