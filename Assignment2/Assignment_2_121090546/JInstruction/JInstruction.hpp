#ifndef _J_INSTRUCTION
#define _J_INSTRUCTION

#include <stdlib.h>
#include <string>

typedef std::string S;
typedef u_int32_t ui32;

static S J_opcode, target;
static unsigned long J_OPCODE, TARGET;

void callJInstruction(S _J_opcode, S _target, ui32 & PC, ui32* regis_0);

void j(ui32 & PC);
void jal(ui32 & PC, ui32* regis_0);
#endif