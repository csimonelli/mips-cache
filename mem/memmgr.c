#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "ram.h"
#include "memmgr.h"
#include "memspy.h"


void write_WT_word(cache_t * cache, ram_t *ram, unsigned int address, unsigned int data) {
    if(cache) {
        fa_header *header;
        header = find_header(address,cache);
        if(!header) {            
            header = CACHE_block_allocate(cache, address);
        } 
       
        CACHE_set_word(cache, header, address, data); 

    }
    RAM_set_word(ram, data, address);

}

unsigned int read_WT_word(cache_t * cache, ram_t * ram, unsigned int address) {
    if(cache) {
        fa_header *header;
        header = find_header(address,cache);
        if(!header) {
            
            header = CACHE_block_allocate(cache, address);

            unsigned int block_address = CACHE_get_block_address(cache, address);
            unsigned int buff_data[CACHE_get_block_size(cache)];
            
            RAM_get_words(ram, buff_data, block_address, CACHE_get_block_size(cache));
            CACHE_set_block(cache, header, address, buff_data); 
        }
    
        return CACHE_get_word(cache, header, address);

    }

    return RAM_get_word(ram, address);
}

void write_WB_word(cache_t * cache, ram_t *ram, unsigned int address, unsigned int data) {
    if(cache) {
        fa_header *header;
        header = find_header(address, cache);

        if(!header) {
            
            header = CACHE_block_allocate(cache, address);
 
            if(CACHE_is_dirty_header(header)){
                unsigned int dirty_block[CACHE_get_block_size(cache)/sizeof(int)];
                size_t dirty_block_address = CACHE_get_block_header_address(cache, header);

                CACHE_get_block(cache, header, dirty_block);
                RAM_set_words(ram, dirty_block, dirty_block_address, CACHE_get_block_size(cache)/sizeof(int));
                CACHE_clean_dirty_flag(header);
            }
        }

        CACHE_set_word(cache, header, address, data);
        CACHE_set_dirty_flag(header);


    } else {
        RAM_set_word(ram, data, address);
    }
}

unsigned int read_WB_word(cache_t * cache,  ram_t* ram, unsigned int address) {
    if(cache) {
        fa_header *header;
        header = find_header(address, cache);

        if(!header) {
            header = CACHE_block_allocate(cache, address);
 
            if(CACHE_is_dirty_header(header)) {
                unsigned int dirty_block[CACHE_get_block_size(cache)/sizeof(int)];
                size_t dirty_block_address = CACHE_get_block_header_address(cache, header);

                CACHE_get_block(cache, header, dirty_block);
                RAM_set_words(ram, dirty_block, dirty_block_address, CACHE_get_block_size(cache)/sizeof(int));
                CACHE_clean_dirty_flag(header);

            }
            unsigned int block_address = CACHE_get_block_address(cache, address);
            unsigned int buff_data[CACHE_get_block_size(cache)/sizeof(int)];
            
            RAM_get_words(ram, buff_data, block_address, CACHE_get_block_size(cache)/sizeof(int));
            CACHE_set_block(cache, header, address, buff_data); 
            CACHE_clean_dirty_flag(header);
        }
    
        return CACHE_get_word(cache, header, address);

    }

    return RAM_get_word(ram, address);
}


memmngr_t *  MEMMGR_create(unsigned int * ram, cache_t * icache, cache_t *dcache, write_policy_t wp) {
    memmngr_t* memmgr = malloc(sizeof(memmngr_t));
    memmgr->ram = RAM_set(ram);
    memmgr->dcache = dcache;
    memmgr->icache = icache;

    if(wp == WB) {
        memmgr->read = &read_WB_word;
        memmgr->write = &write_WB_word;
    } else if(wp == WT) {
        memmgr->read = &read_WT_word;
        memmgr->write = &write_WT_word;
    }

    return memmgr;

}

void MEMMGR_set_spy(memmngr_t *memmgr, void* user_arg,  void (*dhit)  (void*, const cache_t *, const fa_header*), 
                                                        void (*dbmiss)(void*, const cache_t *, const fa_header*),
                                                        void (*damiss)(void*, const cache_t *, const fa_header*),
                                                        void (*ihit)  (void*, const cache_t *, const fa_header*),
                                                        void (*ibmiss)(void*, const cache_t *, const fa_header*),
                                                        void (*iamiss)(void*, const cache_t *, const fa_header*)) {
        if(memmgr->icache) {
            memspy_t *spy = CACHE_get_memspy(memmgr->icache);
            MEMSPY_set_cache_events(spy, ihit, ibmiss, iamiss);
            MEMSPY_set_user_argument(spy, user_arg);
        }
        if(memmgr->dcache) {
            memspy_t *spy = CACHE_get_memspy(memmgr->dcache);
            MEMSPY_set_cache_events(spy, dhit, dbmiss, damiss);
            MEMSPY_set_user_argument(spy, user_arg);
        }
}


int MEMMGR_get_data_word(const memmngr_t *memmgr, unsigned int address) {
    return memmgr->read(memmgr->dcache, memmgr->ram, address);
}

int MEMMGR_get_instruction(const memmngr_t *memmgr, unsigned int address) {
    return memmgr->read(memmgr->icache, memmgr->ram, address);
}

void MEMMGR_write_data_word(const memmngr_t *memmgr, unsigned int address, unsigned int data) {
    memmgr->write(memmgr->dcache, memmgr->ram, address, data);
}