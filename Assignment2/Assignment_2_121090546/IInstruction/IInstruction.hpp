#ifndef _I_INSTRUCTION
#define _I_INSTRUCTION

#include <stdlib.h>
#include <cstdio>
#include <string>

typedef int16_t immediate_t;
typedef std::string S;
typedef u_int32_t mem_t;
typedef u_int32_t instruction_t;
typedef u_int32_t data_t;
typedef u_int32_t ui32;

void callIInstruction(
    S _I_opcode,
    S _rs,
    S _rt,
    S _immediate,
    u_int32_t* regis_0,
    void* real_mem,
    ui32 & PC
);

void addi(ui32* regis_0);
void addiu(ui32* regis_0);
void andi(ui32* regis_0);
void beq(ui32* regis_0, ui32& PC);
void bgez(ui32* regis_0, ui32& PC);
void bgtz(ui32* regis_0, ui32& PC);
void blez(ui32* regis_0, ui32& PC);
void bltz(ui32* regis_0, ui32& PC);
void bne(ui32* regis_0, ui32& PC);
void lb(ui32* regis_0, void* real_mem);
void lbu(ui32* regis_0, void* real_mem);
void lh(ui32* regis_0, void* real_mem);
void lhu(ui32* regis_0, void* real_mem);
void lui(ui32* regis_0, void* real_mem);
void lw(ui32* regis_0, void* real_mem);
void ori(ui32* regis_0);
void sb(ui32* regis_0, void* real_mem);
void slti(ui32* regis_0);
void sltiu(ui32* regis_0);
void sh(ui32* regis_0, void* real_mem);
void sw(ui32* regis_0, void* real_mem);
void xori(ui32* regis_0);
void lwl(ui32* regis_0, void* real_mem);
void lwr(ui32* regis_0, void* real_mem);
void swr(ui32* regis_0, void* real_mem);
void swl(ui32* regis_0, void* real_mem);
#endif