#include <stdio.h>
#include <string.h>
#include "memutils.h"
#include "cache.h"

void MEMUTILS_cache_print(const cache_t *cache, const fa_header* header_highligth, char* highligth) {

    for (size_t i = 0; i < cache->ctrl.data_size/ (cache->ctrl.associativity*cache->ctrl.block_size); i++) {
        printf("IDX: %2lu | ", i);

        for (size_t j = 0; j < cache->ctrl.associativity; j++) {
            printf("set: %2lu | ", j+1);
            char format[50];
            
            if(header_highligth != NULL && highligth != NULL && &(cache->data[i][j]) == header_highligth) {
                strcpy(format, "TAG: %s0x%08X" RESET);

                if(cache->data[i][j].options & CACHE_BLOCK_DIRTY) {
                    strcat(format, "*| ");
                } else {
                    strcat(format, " | ");
                }
                printf(format, highligth, cache->data[i][j].tag);

            } else {

                strcpy(format, "TAG: 0x%08X");
                if(cache->data[i][j].options & CACHE_BLOCK_DIRTY) {
                    strcat(format, "*| ");
                } else {
                    strcat(format, " | ");
                }
                printf(format, cache->data[i][j].tag);
            }          

      
            for (size_t k = 0; k < cache->ctrl.block_size; k++) {
                printf("%02hhx ", cache->data[i][j].data[k]);
            }
             printf(" || ");
        }
        printf("\n");
    }
}

void MEMUTILS_ram_print(const ram_t *ram, unsigned int index, unsigned int count, char* highligth) {
    for (size_t i = 0; i < count; i++)
    {
        printf("ADDR:  %lu | 0x%08X\n", index+i*4, ram->buff[(index+i)/4]);
    }
}