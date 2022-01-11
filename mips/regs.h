#ifndef REGS__H
#define REGS__H

typedef struct reg {
    int regs[32];

} reg_t;

reg_t* REG_create();
void REG_destroy(reg_t* regfile);
void REG_set(reg_t* regfile, int reg_num, int value);
int  REG_get(const reg_t* regfile, int reg_num);

#endif