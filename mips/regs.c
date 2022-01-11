#include "regs.h"
#include <stdlib.h>

reg_t* REG_create() {
    reg_t* regfile = malloc(sizeof(reg_t));
    /* TODO: check*/
    regfile->regs[0] = 0x00000000;
    return  regfile;
}

void REG_destroy(reg_t* regfile) {
    free(regfile);
}

/* TODO: add limits check */
void REG_set(reg_t* regfile, int reg_num, int value) {
    if(!reg_num) return;
    regfile->regs[reg_num] = value;
}

int REG_get(const reg_t* regfile, int reg_num) {
    return regfile->regs[reg_num];
}
