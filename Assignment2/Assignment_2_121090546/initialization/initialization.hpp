#ifndef _INITIALIZATION
#define _INITIALIZATION

#include <stdlib.h>
#include <cstdio>
#include <string>

#include <vector>
#include <bitset>
typedef u_int32_t mem_t;
typedef u_int32_t ui32;
typedef u_int32_t instruction_t;//  store one mips instruction
typedef std::string S;//            abbreviation of std::string
typedef std::bitset<8> b8;//        abbr.
typedef std::bitset<16> b16;//      abbr.
typedef std::bitset<32> b32;//      abbr. 
typedef std::bitset<64> b64;//      abbr.       

void initialization(
    S asmSourceFile, 
    S assembledBinCodesFile, 
    S checkpointsFile, 
    S inputsFile, 
    void* real_mem,
    ui32* regis_0,
    ui32 & PC,
    ui32 & gp,
    ui32 & sp,
    ui32 & fp,
    std::ifstream & f_in,
    std::ofstream & f_out,
    ui32 & dynamic_top
);
void readDataSection(S asmSourceFile, ui32 & dynamic_top, void* real_mem);
void readInstructions(S assembledBinCodesFile, void* real_mem);

mem_t read_ascii(mem_t mem, S s, void* real_mem);
mem_t read_asciiz(mem_t mem, S s, void* real_mem);
mem_t read_word(mem_t mem, int32_t x, void* real_mem);
mem_t read_byte(mem_t mem, std::vector<int8_t> v, void* real_mem);
mem_t read_half(mem_t mem, std::vector<int16_t> v, void* real_mem);


#endif