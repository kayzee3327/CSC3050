#ifndef _SIMULATION
#define _SIMULATION

#include "initialization.hpp"
#include "checkpoint.hpp"

#include <string>
#include <unordered_map>

void simulation(
    std::string asmSourceFile,
    std::string assembledBinCodesFile,
    std::string checkpointsFile,
    std::string inputsFile,
    std::string outputsFile
);
instruction_t getInstruction(mem_t currentPC);

std::unordered_map<std::string, std::string> R_funct{

    {"add", "100000"}, 
    {"addu", "100001"}, 
    {"and", "100100"}, 
    {"div", "011010"}, 
    {"divu", "011011"},
    {"jalr", "001001"}, 
    {"jr", "001000"}, 
    {"mfhi", "010000"}, 
    {"mflo", "010010"}, 
    {"mthi", "010001"},
    {"mtlo", "010011"}, 
    {"mult", "011000"}, 
    {"multu", "011001"}, 
    {"nor", "100111"}, 
    {"or", "100101"},
    {"sll", "000000"}, 
    {"sllv", "000100"}, 
    {"slt", "101010"}, 
    {"sltu", "101011"}, 
    {"sra", "000011"},
    {"srav", "000111"}, 
    {"srl", "000010"}, 
    {"srlv", "000110"}, 
    {"sub", "100010"}, 
    {"subu", "100011"},
    {"syscall", "001100"}, 
    {"xor", "100110"}

};

std::unordered_map<std::string, std::string> I_opcd {

    {"addi", "001000"}, 
    {"addiu", "001001"}, 
    {"andi", "001100"}, 
    {"beq", "000100"}, 
    {"bgez", "000001"},
    {"bgtz", "000111"}, 
    {"blez", "000110"}, 
    {"bltz", "000001"}, 
    {"bne", "000101"},
    {"lb", "100000"}, 
    {"lbu", "100100"}, 
    {"lh", "100001"}, 
    {"lhu", "100101"}, 
    {"lui", "001111"},
    {"lw", "100011"}, 
    {"ori", "001101"}, 
    {"sb", "101000"}, 
    {"slti", "001010"}, 
    {"sltiu", "001011"}, 
    {"sh", "101001"}, 
    {"sw", "101011"}, 
    {"xori", "001110"}, 
    {"lwl", "100010"},
    {"lwr", "100110"}, 
    {"swl", "101010"},
    {"swr", "101110"}
};

std::unordered_map<std::string, std::string> J_opcd{

    {"j", "000010"}, {"jal", "000011"}

};

std::unordered_map<std::string, std::string> rt_notes {
    {"bgez", "00001"},
    {"bgtz", "00000"},
    {"blez", "00000"},
    {"bltz", "00000"},
};
#endif