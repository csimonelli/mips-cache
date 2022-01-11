#include "instruction.h"

unsigned short INSTRUCTION_getOpcode(instruction_t inst) {
    return (inst & INSTRUCTION_OPCODE_MASK) >> INSTRUCTION_OPCODE_SHIFT;
}

unsigned short INSTRUCTION_getRs(instruction_t inst) {
    return (inst & INSTRUCTION_RTYPE_RS_MASK) >> INSTRUCTION_RTYPE_RS_SHIFT;
}

unsigned short INSTRUCTION_getRt(instruction_t inst) {
    return (inst & INSTRUCTION_RTYPE_RT_MASK) >> INSTRUCTION_RTYPE_RT_SHIFT;
}

unsigned short INSTRUCTION_getRd(instruction_t inst) {
    return (inst & INSTRUCTION_RTYPE_RD_MASK) >> INSTRUCTION_RTYPE_RD_SHIFT;
}

unsigned short INSTRUCTION_getFunction(instruction_t inst) {
    return (inst & INSTRUCTION_RTYPE_FUNCTION_MASK) >> INSTRUCTION_RTYPE_FUNCTION_SHIFT;
}

short INSTRUCTION_getImmediate(instruction_t inst) {
    return (inst & INSTRUCTION_ITYPE_IMMEDIATE_MASK) >> INSTRUCTION_ITYPE_IMMEDIATE_SHIFT;
}
