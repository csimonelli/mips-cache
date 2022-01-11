#include <stdlib.h>
#include "emulator.h"
#include "instruction.h"
#include "../mem/memmgr.h"
#include "operation.h"
#include "regs.h"


context_t * EMULATOR_createContext(memmngr_t *memmngr) {
    context_t *c;
    
    if ((c = malloc(sizeof(context_t))) == NULL) return NULL;

    c->opset = OPERATIONS_create();
    if(!c->opset) {
        free(c);
        return NULL;
    }

    c->regfile = REG_create();
    if(!c->regfile) {
        OPERATIONS_destroy(&c->opset);
        free(c);
        return NULL;
    }

    c->memmgr = memmngr;
    
    c->pc = 0;    

    /* TODO: FLAGS, carry y todo eso */

    return c;
}

void EMULATOR_destroyContext(context_t* c) {
    REG_destroy(c->regfile);
    OPERATIONS_destroy(&(c->opset));
    free(c);
}

exception_t EMULATOR_executeNext(context_t *c) {
    instruction_t instruction = MEMMGR_get_instruction(c->memmgr, c->pc);
    operation_t op = OPERATION_getOperation(c->opset, instruction);

    if(!op) {
        return SOME_EXCEPTION;
    }

    return op(instruction, c->regfile, c->memmgr, &(c->pc));
}