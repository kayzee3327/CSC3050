#ifndef _J_INSTRUCTION
#define _J_INSTRUCTION

#include "initialization.hpp"

#include <string>
typedef std::string S;

S opcode, target;

void callJInstruction(S _opcode, S _target);

void j();
void jal();
#endif