#include <stdio.h>
#include <stdlib.h>
#include "cases.h"
#include "bench.h"


program_t * test0(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x240800ff;
    program->mem[1] = 0xffffffff;
    program->mem[2] = 0x1000ffff;
    program->mem[3] = 0x00000000;
    program->mem[4] = 0x00000000;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}

program_t * test1(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24080000;
    program->mem[1] = 0x24090000;
    program->mem[2] = 0x240a000a;
    program->mem[3] = 0x012a082a;
    program->mem[4] = 0x10200005;
    program->mem[5] = 0x00000000;
    program->mem[6] = 0x01094021;
    program->mem[7] = 0x25290001;
    program->mem[8] = 0x1000fffa;
    program->mem[9] = 0x00000000;
    program->mem[10] = 0xffffffff;
    program->mem[11] = 0x1000ffff;
    program->mem[12] = 0x00000000;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}



program_t * case1(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0400;
    program->mem[2] = 0x2529ffff;
    program->mem[3] = 0x1520fffd;
    program->mem[4] = 0x00000000;
    program->mem[5] = 0xffffffff;
    program->mem[6] = END;
    program->mem[256] = 2;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}


program_t * case2(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0404;
    program->mem[2] = 0x2529ffff;
    program->mem[3] = 0x1520fffd;
    program->mem[4] = 0x00000000;
    program->mem[5] = 0xffffffff;
    program->mem[6] = END;
    program->mem[257] = 2;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}

program_t * case3(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0404;
    program->mem[2] = 0x8c0a0408;
    program->mem[3] = 0x2529ffff;
    program->mem[4] = 0x1520fffc;
    program->mem[5] = 0x00000000;
    program->mem[6] = 0xffffffff;
    program->mem[7] = END;
    program->mem[257] = 1;
    program->mem[258] = 2;

    
    program->computer = config(&program->counter, program->mem);
    return program;
}

program_t * case4(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0404;
    program->mem[2] = 0x8c0a0408;
    program->mem[3] = 0x8c0a040c;
    program->mem[4] = 0x2529ffff;
    program->mem[5] = 0x1520fffb;
    program->mem[6] = 0x00000000;
    program->mem[7] = 0xffffffff;
    program->mem[8] = END;
    program->mem[257] = 1;
    program->mem[258] = 2;
    program->mem[259] = 3;

    
    program->computer = config(&program->counter, program->mem);
    return program;
}


program_t * case5(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0404;
    program->mem[2] = 0x8c0a0408;
    program->mem[3] = 0x8c0a040c;
    program->mem[4] = 0x8c0a0410;
    program->mem[5] = 0x2529ffff;
    program->mem[6] = 0x1520fffa;
    program->mem[7] = 0x00000000;
    program->mem[8] = END;
    program->mem[257] = 1;
    program->mem[258] = 2;
    program->mem[259] = 3;
    program->mem[260] = 4;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}

program_t * case_write(context_t * config(counters_t* , unsigned int *)) {
    program_t *program = malloc(sizeof(program_t));
    program->mem = malloc(1024*1024/4);
        
    program->mem[0] = 0x24090064;
    program->mem[1] = 0x8c0a0400;
    program->mem[2] = 0xac0a0404;
    program->mem[3] = 0x2529ffff;
    program->mem[4] = 0x1520fffc;
    program->mem[5] = 0x00000000;
    program->mem[6] = 0xf0ffffff;
    program->mem[7] = 0x1000ffff;
    program->mem[8] = 0x00000000;

    program->mem[256] = 2;
    
    program->computer = config(&program->counter, program->mem);
    return program;
}

