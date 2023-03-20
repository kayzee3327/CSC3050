#ifndef _INITIALIZATION
#define _INITIALIZATION

#include "simulatedMemory.hpp"
#include "simulatedRegisters.hpp"

#include <vector>
typedef u_int32_t instruction_t;// store one mips instruction

void initialization(std::string asmSourceFile, std::string assembledBinCodesFile);
void readDataSection(std::string asmSourceFile);
void readInstructions(std::string assembledBinCodesFile);

std::string toBinary(u_int32_t x);
instruction_t toBinary(std::string s);

mem_t read_ascii(mem_t mem, std::string s);
mem_t read_asciiz(mem_t mem, std::string s);
mem_t read_word(mem_t mem, int32_t x);
mem_t read_byte(mem_t mem, std::vector<int8_t> v);
mem_t read_half(mem_t mem, std::vector<int16_t> v);
#endif