#ifndef MEMMNGR__H
#define MEMMNGR__H
#include "ram.h"
#include "cache.h"
#include "memspy.h"

/* write policy */

typedef enum {WB, WT} write_policy_t;
typedef void (*write_t)(cache_t * cache, ram_t * ram, unsigned int address, unsigned int data);

typedef unsigned int (*read_t)(cache_t * cache, ram_t *ram, unsigned int address);


typedef struct  {
    /* Data cache */
    cache_t *dcache;
    
    /* Instructions cache*/
    cache_t *icache;

    /* write policy */
    write_t write;
    read_t read;

    ram_t * ram;

} memmngr_t;

memmngr_t *  MEMMGR_create(unsigned int * ram, cache_t * icache, cache_t *dcache, write_policy_t wp);

int MEMMGR_get_data_word(const memmngr_t *memmgr, unsigned int address);
int MEMMGR_get_instruction(const memmngr_t *memmgr, unsigned int address);
void MEMMGR_write_data_word(const memmngr_t *memmgr, unsigned int address, unsigned int data);
void MEMMGR_set_spy(memmngr_t *memmgr, void* user_arg,  void (*dhit)  (void*, const cache_t *, const fa_header*), 
                                                        void (*dbmiss)(void*, const cache_t *, const fa_header*),
                                                        void (*damiss)(void*, const cache_t *, const fa_header*),
                                                        void (*ihit)  (void*, const cache_t *, const fa_header*),
                                                        void (*ibmiss)(void*, const cache_t *, const fa_header*),
                                                        void (*iamiss)(void*, const cache_t *, const fa_header*));

#endif
