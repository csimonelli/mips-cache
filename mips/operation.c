#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "../mem/memmgr.h"
#include "regs.h"

exception_t __OPERATIONS_NOT_IMPLEMENTED(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    printf("Operation not implemented - instruction: %i\n", INSTRUCTION_getOpcode(inst));
    (*pc)+=4;

    return NO_EXCEPTION;
}

operation_set OPERATIONS_create() {
    operation_set op = malloc(sizeof(operation_t*) * 64);
    if(!op) return NULL;
    
    /* functions for opcode SPECIAL */
    op[0] = malloc(sizeof(operation_t) * 64);
    /* TODO: if null .... */

    /* Initialice all special function for opcode 000000 */
    for (size_t i = 0; i < 64; i++)
    {
        op[0][i] = &__OPERATIONS_NOT_IMPLEMENTED;
    }
    
    /* Initialice others indexes */
    for (size_t i = 1; i < 64; i++)
    {
        op[i] = malloc(sizeof(operation_t));
        op[i][0] = &__OPERATIONS_NOT_IMPLEMENTED;
    }
    
    /* TODO: Use opcode as index */
    op[0][ 0] = &nop;
    op[0][33] = &addu;
    op[0][42] = &slt;
    op[4][ 0] = &beq;
    op[5][ 0] = &bneq;
    op[9][ 0] = &addiu;
    op[35][0] = &lw;
    op[43][0] = &sw;
    op[60][0] = &end;
    op[63][0] = &dump;

    return op;
}

void OPERATIONS_destroy(operation_set *op) {
    free(op[0][0]);
    free(op[0]);
    *op = NULL;
}

operation_t OPERATION_getOperation(operation_set opset, instruction_t inst) {
    unsigned short opcode = INSTRUCTION_getOpcode(inst);
    if(opcode == 0x0000) {
        unsigned short function = INSTRUCTION_getFunction(inst);
        return opset[opcode][function];
    }
    return opset[opcode][0];
}

exception_t nop(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t addu(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    int Rt = REG_get(regfile, INSTRUCTION_getRt(inst));
    int Rs = REG_get(regfile, INSTRUCTION_getRs(inst));
    REG_set(regfile, INSTRUCTION_getRd(inst), Rt + Rs);
    
    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t addiu(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    int Rs = REG_get(regfile, INSTRUCTION_getRs(inst));
    REG_set(regfile, INSTRUCTION_getRt(inst), Rs + INSTRUCTION_getImmediate(inst));
    
    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t li  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    REG_set(regfile, INSTRUCTION_getRt(inst), INSTRUCTION_getImmediate(inst));

    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t beq (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    /* TODO: Jumps and branches execute the next intruction before jumping    */
    /* something like:                                                        */
    /* pc = OPERATION_getOperation(opset, *inst1)(*inst1, &regfile, mem, pc); */
    if(REG_get(regfile, INSTRUCTION_getRt(inst)) != REG_get(regfile, INSTRUCTION_getRs(inst))) {
        (*pc)+=4;
        return NO_EXCEPTION;
    }
    *pc += ((1 + INSTRUCTION_getImmediate(inst))*4);
    return NO_EXCEPTION;
}

exception_t bneq (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    /* TODO: Jumps and branches execute the next intruction before jumping    */
    /* something like:                                                        */
    /* pc = OPERATION_getOperation(opset, *inst1)(*inst1, &regfile, mem, pc); */
    if(REG_get(regfile, INSTRUCTION_getRt(inst)) == REG_get(regfile, INSTRUCTION_getRs(inst))) {
        (*pc)+=4;
        return NO_EXCEPTION;
    }
    *pc += ((1 + INSTRUCTION_getImmediate(inst))*4);
    return NO_EXCEPTION;
}

exception_t slt (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    int Rt = REG_get(regfile, INSTRUCTION_getRt(inst));
    int Rs = REG_get(regfile, INSTRUCTION_getRs(inst));
    REG_set(regfile, INSTRUCTION_getRd(inst), Rs < Rt);

    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t lw (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    int data = MEMMGR_get_data_word(mmngr, INSTRUCTION_getImmediate(inst));
    REG_set(regfile, INSTRUCTION_getRt(inst), data);
    printf("DEBUG: lw read: %i from addres: %i\n", data, INSTRUCTION_getImmediate(inst));

    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t sw (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    int data = REG_get(regfile, INSTRUCTION_getRt(inst));
    MEMMGR_write_data_word(mmngr, INSTRUCTION_getImmediate(inst), data);
    printf("DEBUG: sw write: %i to addres: %i\n", data, INSTRUCTION_getImmediate(inst));

    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t dump(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    for (short i = 0; i < 32; i++) {
        printf("Reg %d: %d\n", i, REG_get(regfile, i));
    }
    
    (*pc)+=4;
    return NO_EXCEPTION;
}

exception_t end(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc) {
    printf("End\n");
    return END_PROGRAM;
}