#include <stdio.h>
#include <stdlib.h>

#include "bench.h"
#include "../mem/cache.h"
#include "../mem/memutils.h"


void dhit(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Data hit\n");
    MEMUTILS_cache_print(cache, header, BOLDBLUE);
    ((counters_t*)counters)->data_hits++;
}

void dbmiss(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Data miss before alloc\n");
    MEMUTILS_cache_print(cache, header, BOLDRED);
    ((counters_t*)counters)->data_misses++;
}

void damiss(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Data miss after alloc\n");
    MEMUTILS_cache_print(cache, header, BOLDGREEN);

}

void ihit(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Istruction hit\n");
    MEMUTILS_cache_print(cache, header, BOLDBLUE);
    ((counters_t*)counters)->instruction_hits++;
}

void ibmiss(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Instruction miss before alloc\n");
    MEMUTILS_cache_print(cache, header, BOLDRED);
    ((counters_t*)counters)->instruction_misses++;
}

void iamiss(void * counters, const cache_t * cache, const fa_header* header) {
    printf("Instruction miss after alloc\n");
    MEMUTILS_cache_print(cache, header, BOLDGREEN);

}

void reset_counter(counters_t* counters) {
    counters->data_hits = 0;
    counters->data_misses = 0;
    counters->instruction_hits = 0;
    counters->instruction_misses = 0;
    counters->instruction_count = 0;
}





