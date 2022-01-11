#ifndef EMULATOR__H
#define EMULATOR__H

#include "operation.h"
#include "regs.h"
#include "../mem/memmgr.h"

typedef struct context__ {
    reg_t* regfile;
    operation_set opset;
    size_t pc;
    //unsigned int * ram;
    /* TODO: It does nothing in CREATE */
    unsigned char status; /**overflow, carry, etc**/
    memmngr_t* memmgr;
} context_t;

exception_t EMULATOR_executeNext(context_t *);
void EMULATOR_destroyContext(context_t *);
context_t * EMULATOR_createContext(memmngr_t *memmngr);



#endif