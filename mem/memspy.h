#ifndef MEMSPY__H
#define MEMSPY__H
#include "cache.h"

typedef struct memspy_t {
    void* user_arg;
    void (*onRamWrite)(void* user_arg, unsigned int addres, const unsigned int* old_value, 
                                        const unsigned int* new_value, unsigned int count);
    void (*onRamRead)(void* user_arg, unsigned int addres, const unsigned int* value,  unsigned int count);
    void (*onCacheHit)(void* user_arg, const cache_t*, const fa_header*);
    void (*onCacheBeforeAlloc)(void* user_arg, const cache_t*, const fa_header*);
    void (*onCacheAfterAlloc)(void* user_arg, const cache_t*, const fa_header*);

} memspy_t;

memspy_t * MEMSPY_create();
void MEMSPY_set_defaults(memspy_t *spy);

void MEMSPY_on_cache_beforeAlloc(memspy_t *spy, const cache_t *cache, const fa_header *header);
void MEMSPY_on_cache_afterAlloc(memspy_t *spy, const cache_t *cache, const fa_header *header);
void MEMSPY_on_cache_hit(memspy_t *spy, const cache_t *cache, const fa_header *header);


void MEMSPY_set_user_argument(memspy_t *spy, void* user_arg);
void MEMSPY_set_cache_events(memspy_t *spy, void (*hit  )(void* , const cache_t *, const fa_header*), 
                                            void (*bmiss)(void* , const cache_t *, const fa_header*), 
                                            void (*amiss)(void* , const cache_t *, const fa_header*));

#endif