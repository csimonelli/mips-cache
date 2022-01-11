#ifndef CASES__H
#define CASES__H
#include "../mips/emulator.h"
#include "bench.h"

#define END 0xf0ffffff
typedef struct program_t {
    unsigned int *mem;
    counters_t counter;
    context_t* computer;
}program_t;


program_t * test0(context_t * config(counters_t* , unsigned int *));
program_t * test1(context_t * config(counters_t* , unsigned int *));
program_t * case1(context_t * config(counters_t* , unsigned int *));
program_t * case2(context_t * config(counters_t* , unsigned int *));
program_t * case3(context_t * config(counters_t* , unsigned int *));
program_t * case4(context_t * config(counters_t* , unsigned int *));
program_t * case5(context_t * config(counters_t* , unsigned int *));
program_t * case_write(context_t * config(counters_t* , unsigned int *));

#endif