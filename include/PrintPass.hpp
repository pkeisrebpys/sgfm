#ifndef PRINT_PASS_HPP
#define PRINT_PASS_HPP

#include <cstdio>
#define PRINT_PASS(arg) fprintf(stderr,"%s,%d:%s\n",__FILE__,__LINE__,arg)
#endif
