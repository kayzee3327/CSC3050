#ifndef _R_INSTRUCTION
#define _R_INSTRUCTION

#include "initialization.hpp"

#include <string>
typedef std::string S; // abbreviation of std::string

S rs, rt, rd, sa, function;
void callRInstruction(
    S _rs,
    S _rt,
    S _rd,
    S _sa,
    S _function
);

void add();
void addu();
void _and();
void div();
void divu();
void jalr();
void jr();
void mfhi();
void mflo();
void mthi();
void mtlo();
void mult();
void multu();
void nor();
void _or();
void sll();
void sllv();
void slt();
void sltu();
void sra();
void srav();
void srl();
void srlv();
void sub();
void subu();
void _xor();
void syscall();

#endif