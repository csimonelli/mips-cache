#ifndef CACHE__H
#define CACHE__H
#include <bits/types/clock_t.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>


#define CACHE_BLOCK_VALID 0x00000001
#define CACHE_BLOCK_DIRTY 0x00000002

typedef enum {MISS, HIT} match_t;

typedef struct {
    size_t options;
    size_t timestamp;
    size_t tag;
    /* first byte addres */
    size_t address;
    char * data;
} fa_header;

typedef struct cache_t {
    struct {
        size_t block_size;
        size_t data_size;
        
        size_t INDEX_MASK;
        size_t OFFSET_MASK;
        size_t TAG_MASK;
        
        unsigned char INDEX_SHIFT;
        unsigned char OFFSET_SHIFT;
        //unsigned char TAG_SHIFT;
        
        unsigned char associativity;

    } ctrl;
    
    fa_header* (*eviction_policy) (unsigned int address, const struct cache_t* cache);

    fa_header ** data;

    struct memspy_t * spy;


} cache_t;

cache_t * CACHE_Create_SA(unsigned char associativity, size_t block_size, size_t data_size, 
    fa_header* (*eviction_policy) (unsigned int address, const cache_t* cache));

cache_t * CACHE_create_mixed_from_cache(const cache_t * cache);


void CACHE_set_block(const cache_t *cache, fa_header* header, unsigned int address, const unsigned int* block);
void CACHE_set_word(const cache_t *cache, fa_header* header, unsigned int address, unsigned data);
void CACHE_update_time_stamp(fa_header* header);

void CACHE_get_block(const cache_t *cache, const fa_header* header, unsigned int* data);
void CACHE_clean_dirty_flag(fa_header *header);
void CACHE_set_dirty_flag(fa_header *header);

unsigned int CACHE_get_word(const cache_t *cache, fa_header *header, unsigned int address);

fa_header* CACHE_block_allocate(const cache_t *cache,  unsigned int address);
fa_header* find_header(size_t address, const cache_t* cache);
fa_header* eviction_policy_lru(unsigned int address, const cache_t* cache);

size_t CACHE_is_dirty_header(const fa_header *header);
size_t CACHE_get_block_address(const cache_t *cache, unsigned int address);
size_t CACHE_get_block_header_address(const cache_t *cache, const fa_header* header);
size_t CACHE_get_block_size(const cache_t *cache);

struct memspy_t * CACHE_get_memspy(const cache_t *cache);

#endif