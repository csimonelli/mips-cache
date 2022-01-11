#include <stdio.h>
#include <stdlib.h>

#include "bench.h"
#include "cases.h"
#include "../mips/emulator.h"
#include <curl/curl.h>

void print_program_stats(const counters_t * counters) {

    printf("Instruccines: %lu\n", counters->instruction_count);
    printf("    DATA  HITS: %8lu - DATA  MISSES: %8lu \n", counters->data_hits, counters->data_misses);
    printf("    INST  HITS: %8lu - INST  MISSES: %8lu \n", counters->instruction_hits, counters->instruction_misses - 3);
    printf("    TOTAL HITS: %8lu - TOTAL MISSES: %8lu\n", counters->data_hits + counters->instruction_hits, counters->data_misses + counters->instruction_misses -3);
    printf("    Accesos totales a memoria: %lu\n",  counters->data_hits + counters->data_misses + counters->instruction_hits + counters->instruction_misses -3);
    double total_misses =  counters->data_misses + counters->instruction_misses - 3; // NOP + DUMP + END
    double total_mem_acces = counters->data_hits + counters->instruction_hits + counters->data_misses + counters->instruction_misses - 3; // NOP + DUMP + END

    printf("    miss rate: %6.2f %%\n",  100*total_misses/total_mem_acces);
}

void run(program_t* program) {
    int i = 0;
    for (i=0; i<1000; i++) {
        program->counter.instruction_count++;
        if(EMULATOR_executeNext(program->computer) != NO_EXCEPTION)
            break;

    }
    print_program_stats(&program->counter);

    //EMULATOR_destroyContext(program->counter);

}

context_t * computadora_DM_TP(counters_t* counters, unsigned int *ram) {
    reset_counter(counters);


    cache_t* dcache = CACHE_Create_SA(1, 4, 64, NULL);
    //cache_t* icache = CACHE_Create_SA(1, 1, 32, NULL);
    cache_t* icache = CACHE_create_mixed_from_cache(dcache);

    memmngr_t * mmu = MEMMGR_create(ram, icache, dcache, WT);
    MEMMGR_set_spy(mmu, counters, &dhit, &dbmiss, &damiss, &ihit, &ibmiss, &iamiss);
    return  EMULATOR_createContext(mmu);
}

context_t * computadora_2WSA_TP(counters_t* counters, unsigned int *ram) {
    reset_counter(counters);


    cache_t* dcache = CACHE_Create_SA(2, 4, 32, NULL);
    cache_t* icache = CACHE_create_mixed_from_cache(dcache);

    memmngr_t * mmu = MEMMGR_create(ram, icache, dcache, WT);
    MEMMGR_set_spy(mmu, counters, &dhit, &dbmiss, &damiss, &ihit, &ibmiss, &iamiss);
    return  EMULATOR_createContext(mmu);
}

context_t * computadora_FA_TP(counters_t* counters, unsigned int *ram) {
    reset_counter(counters);

    cache_t* dcache = CACHE_Create_SA(8, 1, 32, NULL);
    cache_t* icache = CACHE_create_mixed_from_cache(dcache);
    memmngr_t * mmu = MEMMGR_create(ram, icache, dcache, WT);
    MEMMGR_set_spy(mmu, counters, &dhit, &dbmiss, &damiss, &ihit, &ibmiss, &iamiss);
    return  EMULATOR_createContext(mmu);
}

context_t * computadora_no_cache(counters_t* counters, unsigned int *ram) {
    reset_counter(counters);

    memmngr_t * mmu = MEMMGR_create(ram, NULL, NULL, WT);
    MEMMGR_set_spy(mmu, counters, &dhit, &dbmiss, &damiss, &ihit, &ibmiss, &iamiss);
    return  EMULATOR_createContext(mmu);
}

int main(void) {
    printf("Punto 1:\n");
    //run(case1(computadora_DM_TP));
    //run(case2(computadora_DM_TP));
    //run(case3(computadora_DM_TP));
    //run(case4(computadora_DM_TP));
    run(case5(computadora_FA_TP));
//
    //printf("Punto 2:\n");
    //run(case4(computadora_DM_TP));
    //run(case4(computadora_2WSA_TP));
    //run(case4(computadora_FA_TP));
    // test write 
    //run(case_write(computadora_DM_TP));
    //run(test0(computadora_no_cache));
}
