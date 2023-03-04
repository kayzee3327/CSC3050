#ifndef _PHASE_2_HPP
#define _PHASE_2_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "labelTable.hpp"

typedef std::vector<std::string > InstructionPartVec;

// what_type:
// tell what type of mips instruction the line is
// @param  
//     string: a raw instruction line from .asm file
// @return 
//     char: one of types 'R', 'I', 'J'
char what_type(std::string instruction);

// get_offset_str:
// get the offset in the form "offset(base)"
// @param
//     string: a string of form "offset(base)"
// @return
//     string: offset in decimal form with type string
std::string get_offset_str(std::string offsetAndBase);

// get_offset_str_branch:
// calculate the offset for branch instructions
// @param
//     unsigned int: the address value of program counter
//     unsigned int: the address of specific label
// @return
//     string: the binary result of calculation with type string
std::string get_offset_str_branch(unsigned int PC, unsigned int target);

// get_base_str:
// get the base in the form "offset(base)"
// @param
    // string: a string of form "offset(base)"
// @return
    // string: base register with type string
std::string get_base_str(std::string offsetAndBase);

// translate:
// translate a line of instruction, pass splited instruction into translate_R/I/J
// @param
//     string: a line of instruction
// @return
//     string: binary string of translated instuction
std::string translate(std::string line);  // break an instruction into parts

// translate_R:
// translate an R instruction into binary form
// @param
    // InstructionPartVec: a splited instruction
// @return
    // string: binary form of input instruction 
std::string translate_R(InstructionPartVec parts);

// translate_I:
// translate an I instruction into binary form
// @param
    // InstructionPartVec: a splited instruction
// @return
    // string: binary form of input instruction 
std::string translate_I(InstructionPartVec parts);

// translate_J:
// translate an J instruction into binary form
// @param
    // InstructionPartVec: a splited instruction
// @return
    // string: binary form of input instruction 
std::string translate_J(InstructionPartVec parts);

void phase2(std::string inputFilePath, std::string outputFilePath, LabelTable l);

#endif

