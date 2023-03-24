#ifndef _R_INSTRUCTION
#define _R_INSTRUCTION

#include "Syscall.hpp"
#include <stdlib.h>
#include <cstdio>
#include <string>

typedef std::string S;
typedef u_int32_t ui32;
static S R_rs, R_rt, rd, sa, function;
static unsigned long R_RS, R_RT, RD, SA, FUNCTION;

void callRInstruction(
    S _rs,
    S _rt,
    S _rd,
    S _sa,
    S _function,
    ui32* regis_0,
    ui32 & HI,
    ui32 & LO,
    ui32 & PC, 
    FILE* f_in, FILE* f_out, 
    unsigned long real_mem, 
    ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, ui32 & dynamic_top
);

void add(ui32* regis_0);
void addu(ui32* regis_0);
void _and(ui32* regis_0);
void div(ui32* regis_0, ui32 & LO, ui32 & HI);
void divu(ui32* regis_0, ui32 & LO, ui32 & HI);
void jalr(ui32* regis_0, ui32 & PC);
void jr(ui32* regis_0, ui32 & PC);
void mfhi(ui32* regis_0, ui32 & HI);
void mflo(ui32* regis_0, ui32 & LO);
void mthi(ui32* regis_0, ui32 & HI);
void mtlo(ui32* regis_0, ui32 & LO);
void mult(ui32* regis_0, ui32 & HI, ui32 & LO);
void multu(ui32* regis_0, ui32 & HI, ui32 & LO);
void nor(ui32* regis_0);
void _or(ui32* regis_0);
void sll(ui32* regis_0);
void sllv(ui32* regis_0);
void slt(ui32* regis_0);
void sltu(ui32* regis_0);
void sra(ui32* regis_0);
void srav(ui32* regis_0);
void srl(ui32* regis_0);
void srlv(ui32* regis_0);
void sub(ui32* regis_0);
void subu(ui32* regis_0);
void _xor(ui32* regis_0);


#endif