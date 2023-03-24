#ifndef _SIMULATION
#define _SIMULATION

#include <string>
#include <unordered_map>
#include <stdlib.h>
typedef u_int32_t mem_t;
typedef u_int32_t instruction_t;
typedef u_int32_t ui32;
typedef std::string S;

void simulation(
    S asmSourceFile,
    S assembledBinCodesFile,
    S checkpointsFile,
    S inputsFile,
    S outputsFile,
    u_int32_t* regis_0, 
    u_int32_t & PC, 
    u_int32_t & LO, 
    u_int32_t & HI,
    void* real_mem,
    mem_t & fp,
    mem_t & sp,
    mem_t & gp,
    FILE *f_in, 
    FILE *f_out,
    u_int32_t & currentHeapBlock, 
    u_int32_t & currentHeapBlock_size, 
    u_int32_t & dynamic_top 
);
instruction_t getInstruction(mem_t currentPC, unsigned long real_mem);
void callInstruction(
    S currentInsStr, ui32 *regis_0, ui32 &HI, ui32 &LO, ui32 &PC, 
    FILE *f_in, FILE *f_out, unsigned long real_mem, ui32 &currentHeapBlock, 
    ui32 &currentHeapBlock_size, ui32 &dynamic_top
);

#endif