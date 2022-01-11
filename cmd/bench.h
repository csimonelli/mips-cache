#ifndef BENCH__H
#define BENCH__H
#include <stdio.h>
#include "../mem/cache.h"

typedef struct counters_t {
    size_t data_misses;
    size_t data_hits;
    size_t instruction_misses;
    size_t instruction_hits;
    size_t instruction_count;
} counters_t;


// callbacks
void dhit(void * counters, const cache_t * cache, const fa_header* header);
void dbmiss(void * counters, const cache_t * cache, const fa_header* header);
void damiss(void * counters, const cache_t * cache, const fa_header* header);
void ihit(void * counters, const cache_t * cache, const fa_header* header);
void ibmiss(void * counters, const cache_t * cache, const fa_header* header);
void iamiss(void * counters, const cache_t * cache, const fa_header* header) ;
void reset_counter(counters_t* counters);




#endif
