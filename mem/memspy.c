#include <stdio.h>
#include <stdlib.h>
#include "memspy.h"
#include "cache.h"

void onRamWriteDefault(void* user_arg, unsigned int addres, const unsigned int* old_value, 
                                    const unsigned int* new_value, unsigned int count) { }
void onRamReadDefault(void* user_arg, unsigned int addres, const unsigned int* value,  unsigned int count){ }
void onCacheDefault(void* user_arg, const cache_t *cache, const fa_header* header) { }


void MEMSPY_set_defaults(memspy_t *spy) {
    spy->onRamRead = &onRamReadDefault;
    spy->onRamWrite = &onRamWriteDefault;
    spy->onCacheHit = &onCacheDefault;
    spy->onCacheBeforeAlloc = &onCacheDefault;
    spy->onCacheAfterAlloc = &onCacheDefault;
}

memspy_t * MEMSPY_create() {
    memspy_t * spy = malloc(sizeof(memspy_t));
    MEMSPY_set_defaults(spy);

    return spy;
}

void MEMSPY_on_cache_hit(memspy_t *spy, const cache_t *cache, const fa_header *header) {
    spy->onCacheHit(spy->user_arg, cache, header);
}

void MEMSPY_on_cache_beforeAlloc(memspy_t *spy, const cache_t *cache, const fa_header *header) {
    spy->onCacheBeforeAlloc(spy->user_arg, cache, header);
}

void MEMSPY_on_cache_afterAlloc(memspy_t *spy, const cache_t *cache, const fa_header *header) {
    spy->onCacheAfterAlloc(spy->user_arg, cache, header);
}

void MEMSPY_set_user_argument(memspy_t *spy, void* user_arg) {
    spy->user_arg = user_arg;
}
void MEMSPY_set_cache_events(memspy_t *spy, void (*hit  )(void* , const cache_t *, const fa_header*), 
                                            void (*bmiss)(void* , const cache_t *, const fa_header*), 
                                            void (*amiss)(void* , const cache_t *, const fa_header*)) {
                                                
    spy->onCacheHit = hit != NULL ? hit : onCacheDefault;
    spy->onCacheBeforeAlloc = bmiss != NULL ? bmiss : onCacheDefault;
    spy->onCacheAfterAlloc = amiss != NULL ? amiss : onCacheDefault;
}
