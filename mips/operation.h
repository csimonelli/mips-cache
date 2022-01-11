#ifndef OPERATION__H
#define OPERATION__H

#include <stdio.h>
#include "instruction.h"
#include "regs.h"
#include "../mem/memmgr.h"

typedef  enum { NO_EXCEPTION, SOME_EXCEPTION, END_PROGRAM } exception_t;

typedef exception_t (*operation_t)(instruction_t, reg_t*, memmngr_t * mmngr, size_t*);
typedef operation_t** operation_set;

operation_set OPERATIONS_create();
void OPERATIONS_destroy(operation_set *);
operation_t OPERATION_getOperation(operation_set, instruction_t);

exception_t nop  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t li   (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t beq  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t bneq (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t addiu(instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t addu (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t slt  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t lw   (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t sw   (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t beq  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t dump (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);
exception_t end  (instruction_t inst, reg_t* regfile, memmngr_t * mmngr, size_t* pc);


#endif