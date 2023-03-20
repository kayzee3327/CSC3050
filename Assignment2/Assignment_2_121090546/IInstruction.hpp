#ifndef _I_INSTRUCTION
#define _I_INSTRUCTION

#include "initialization.hpp"

#include <string>
typedef std::string S;

S opcode, rs, rt, immediate;

void callIInstruction(
    S _opcode,
    S _rs,
    S _rt,
    S _immediate
);

void addi();
void addiu();
void andi();
void beq();
void bgez();
void bgtz();
void blez();
void bltz();
void bne();
void lb();
void lbu();
void lh();
void lhu();
void lui();
void lw();
void ori();
void sb();
void slti();
void sltiu();
void sh();
void sw();
void xori();
void lwl();
void lwr();
void swr();
void swl();
#endif