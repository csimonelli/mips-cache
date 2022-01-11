#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <netinet/in.h>
#include "cache.h"
#include "memspy.h"


// este bardo es para los bytes
/*
match_t CACHE_get_word(const cache_t *cache, unsigned int address, int * data) {
    fa_header *header = find_header( address, cache);

    if(header) {
        size_t offset = address & cache->ctrl.OFFSET_MASK;
        // TODO: no dejar que pidan mas de lo que se puede pedir.
        // hacer el checkeo de offset + sizepedido < sizebloque
        // TODO: Ver lo de net2 otra cosa
        unsigned int host_int;
        memcpy(&host_int, &header->data[offset], sizeof(int));
        *data = htonl(host_int);
        return HIT;
    }

    return MISS;
} 
*/

size_t get_offset(const cache_t *cache, unsigned int address) {
    return address & cache->ctrl.OFFSET_MASK;
}


/**
 * @brief Gets a word from a cache
 * 
 * @param cache the cache 
 * @param address the address 
 * @param data buffer in where the data will be stored
 * @return match_t MISS or HIT
 */
unsigned int CACHE_get_word(const cache_t *cache, fa_header *header, unsigned int address) {
    size_t offset = address & cache->ctrl.OFFSET_MASK;
    return  ntohl(((int*)header->data)[offset/sizeof(int)]);

}


/**
 * @brief Gives the block address of some data that is pointed from the address param
 *        it uses the cache configuration to do so.
 *        For example if the addres 0x00ff0011 and the offset mask is 0x000000ff
 *        the block address will be 0x00ff0000.
 * 
 * @param cache The cache
 * @param address The address
 * @return unsigned int block address
 */
size_t CACHE_get_block_address(const cache_t *cache, unsigned int address) {
    return address & ~cache->ctrl.OFFSET_MASK;
}

size_t CACHE_get_block_header_address(const cache_t *cache, const fa_header* header) {
    return header->address & ~cache->ctrl.OFFSET_MASK;

}


/* wip */
/**
 * @brief Finds some data inside the cache. If the data is stored 
 *        it returns a header in where this data is placed, NULL otherwise
 * @param address Data address
 * @param cache the cache
 * @return fa_header* 
 */
fa_header* find_header(size_t address, const cache_t* cache) {
    size_t index = (address & cache->ctrl.INDEX_MASK) >> cache->ctrl.INDEX_SHIFT;
    fa_header *p = cache->data[index];
    for(int i = 0; i < cache->ctrl.associativity ; i++) {
        if(p[i].tag  == (address & cache->ctrl.TAG_MASK) && p[i].options & 0x00000001) { /* make a valid mask */
            CACHE_update_time_stamp(&p[i]); /* si lo leen le actualizo el timestamp */ 
            if(cache->spy) {
                MEMSPY_on_cache_hit(cache->spy, cache, &p[i]);
            }
            return &p[i];
        }
    }
    
    return NULL;
}

fa_header* CACHE_block_allocate(const cache_t *cache,  unsigned int address) {
    fa_header* header;
    header = cache->eviction_policy(address, cache);
    if(cache->spy) {
        MEMSPY_on_cache_beforeAlloc(cache->spy, cache, header);
    }
    
    return header;
}

void CACHE_set_block(const cache_t *cache, fa_header* header, unsigned int address, const unsigned int* block) { 
    for(int i = 0; i < cache->ctrl.block_size/sizeof(int); i++) {
        int data = htonl(block[i]);
        memcpy(&(header->data[i*sizeof(int)]), &data, sizeof(int));
    }
    
    header->tag =  address & cache->ctrl.TAG_MASK;
    header->address = address;
    header->options|= CACHE_BLOCK_VALID; /* TODO: a function for this */
    CACHE_update_time_stamp(header);
    if(cache->spy) {
        MEMSPY_on_cache_afterAlloc(cache->spy, cache, header);
    }


}

void CACHE_set_word(const cache_t *cache, fa_header* header, unsigned int address, unsigned data) { 
    ((int*)header->data)[get_offset(cache, address)/4] = htonl(data);
    
    header->tag =  address & cache->ctrl.TAG_MASK;
    header->address = address;
    header->options|= CACHE_BLOCK_VALID; /* TODO: a function for this */
    CACHE_update_time_stamp(header);
    if(cache->spy) {
        MEMSPY_on_cache_afterAlloc(cache->spy, cache, header);
    }


}
/** wip*/

void CACHE_update_time_stamp(fa_header* header) {
        header->timestamp = clock(); 
}

void CACHE_get_block(const cache_t *cache, const fa_header* header, unsigned int* data) {
    for(int i = 0; i < cache->ctrl.block_size/sizeof(int); i++) {
        data[i] = ntohl(((int*)header->data)[i]);
    }
}

/**
 * @brief Creates a generic cache. This could be set associative full associative
 *        or direct mapped.
 * 
 * @param associativity for direct mapped this must be 1
 * @param block_size Words per block
 * @param data_size data size in bytes
 * @param ep Pointer to a funtion from the eviction policy, if NULL the LRU will be used
 * @return cache_t* A cache
 */
cache_t * CACHE_Create_SA(unsigned char associativity, size_t block_size, size_t data_size, 
    fa_header* (*ep) (unsigned int, const cache_t*)) {
    cache_t *cache = malloc(sizeof(cache_t));
    cache->ctrl.associativity = associativity;
    cache->ctrl.block_size = block_size*sizeof(int);
    cache->ctrl.data_size = data_size;
    
    /* the defaul eviction policy is LRU */
    if(ep) {
        cache->eviction_policy = ep;
    } else {
        cache->eviction_policy = &eviction_policy_lru;        
    }
    
    // TODO: es porencia de 2 lo que me pasaron? es importante
    unsigned char data_exponent = log2(cache->ctrl.block_size);
    cache->ctrl.OFFSET_MASK = ~(0xFFFFFFFF << data_exponent);
    cache->ctrl.OFFSET_SHIFT = 0;

    unsigned char index_exponent = log2(data_size / (associativity*cache->ctrl.block_size));

    unsigned char tag_exponent = index_exponent + data_exponent;
    cache->ctrl.TAG_MASK = 0xFFFFFFFF << tag_exponent;

    cache->ctrl.INDEX_MASK = 0xFFFFFFFF & ~cache->ctrl.OFFSET_MASK & ~cache->ctrl.TAG_MASK;
    cache->ctrl.INDEX_SHIFT = cache->ctrl.OFFSET_SHIFT + data_exponent;

    cache->spy = MEMSPY_create();

    /* TODO: delete */
    printf("DEBUG: Tag mask: %#010X\n", cache->ctrl.TAG_MASK);
    printf("DEBUG: Index mask: %#010X\n", cache->ctrl.INDEX_MASK);
    printf("DEBUG: Offset mask: %#010X\n", cache->ctrl.OFFSET_MASK);


    cache->data = malloc(sizeof(fa_header*) * data_size / (associativity*cache->ctrl.block_size));
    for(size_t i = 0 ; i < data_size / (associativity*cache->ctrl.block_size); i++) {
        cache->data[i] = malloc(associativity * sizeof(fa_header));
        memset(cache->data[i], 0, associativity * sizeof(fa_header));
        for(size_t j = 0 ; j < associativity; j++) {
            cache->data[i][j].data = malloc(cache->ctrl.block_size);
        }
    }
    return cache;
}

cache_t * CACHE_create_mixed_from_cache(const cache_t * cache) {
    cache_t * copy_cache = malloc(sizeof(cache_t));
    memcpy(copy_cache, cache, sizeof(cache_t));
    copy_cache->spy = MEMSPY_create();
    return copy_cache;
}

memspy_t * CACHE_get_memspy(const cache_t *cache) {
    return cache->spy;
}

size_t CACHE_is_dirty_header(const fa_header *header) {
    return header->options & CACHE_BLOCK_DIRTY;
}

void CACHE_clean_dirty_flag(fa_header *header) {
    header->options &= ~CACHE_BLOCK_DIRTY;
}

void CACHE_set_dirty_flag(fa_header *header) {
    header->options |= CACHE_BLOCK_DIRTY;
}

size_t CACHE_get_block_size(const cache_t *cache) {
    return cache->ctrl.block_size;
}

fa_header* eviction_policy_lru(unsigned int address, const cache_t* cache) {
    size_t index = (address & cache->ctrl.INDEX_MASK) >> cache->ctrl.INDEX_SHIFT;
    fa_header *p = cache->data[index];
    int lru = 0;
    
    for(int i = 0; i < cache->ctrl.associativity ; i++) {
        if(!(p[i].options & CACHE_BLOCK_VALID)) { // if this is not valid, its free!
            lru = i;
            break;
        }
        if(p[i].timestamp  < p[lru].timestamp) {
            lru = i;
        }

    }
    return &p[lru];
}

