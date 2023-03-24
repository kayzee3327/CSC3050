#include "JInstruction.hpp"
#include "conversion.hpp"
#include <unordered_map>
#include <iostream>

static std::unordered_map<S, S> J_opcd{

    {"j", "000010"}, {"jal", "000011"}

};

void callJInstruction(S _J_opcode, S _target, ui32 & PC, ui32* regis_0){
    J_opcode = _J_opcode;
    target = _target;
    J_OPCODE = binstrToUL(J_opcode);
    TARGET = binstrToUL(target);
    if (J_opcode == J_opcd["j"]) {
        j(PC);
    }
    else if (J_opcode == J_opcd["jal"]) {
        jal(PC, regis_0);
    }
    else {
        std::cout << "<callJInstruction> Invalid J_opcode: " << J_opcode << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        exit(0);
    }
}

void j(ui32 & PC){
    b32 bs(toBinary32str(PC).substr(0,4) + target + "00");
    PC = bs.to_ulong();
}
void jal(ui32 & PC, ui32* regis_0){
    *(regis_0 + 32) = PC + 4;
    b32 bs(toBinary32str(PC).substr(0,4) + target + "00");
    PC = bs.to_ulong();
}