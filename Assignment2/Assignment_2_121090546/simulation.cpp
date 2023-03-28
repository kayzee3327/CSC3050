#include "simulation.hpp"
#include "./RInstruction/RInstruction.hpp"
#include "./JInstruction/JInstruction.hpp"
#include "./IInstruction/IInstruction.hpp"
#include "simulatedRegisters.hpp"
#include "simulatedMemory.hpp"
#include "./initialization/initialization.hpp"
#include "./checkpoint/checkpoint.hpp"
#include "conversion.hpp"

#include <string.h>
#include <iostream>

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
    std::ifstream & f_in, 
    std::ofstream & f_out,
    u_int32_t & currentHeapBlock, 
    u_int32_t & currentHeapBlock_size, 
    u_int32_t & dynamic_top 
) {
    
    
    initialization(
        asmSourceFile, assembledBinCodesFile, checkpointsFile, inputsFile, 
        real_mem, regis_0, PC, gp, sp, fp, f_in, f_out, dynamic_top);
    init_checkpoints(checkpointsFile.c_str());
    instruction_t currentIns;
    S currentInsStr;
    int ins_count = 0;

    while(true) {
        currentIns = getInstruction(PC, real_mem);
        if(currentIns != 0){
            currentInsStr = toBinary32str(currentIns);
        }
        else {
            std::cout << "simulation finished." << std::endl;
            std::cout << "PC - 4: " << PC - 4;
            break;
        }
        PC += 4;
        callInstruction(
            currentInsStr, regis_0, HI, LO, PC, f_in, f_out, 
            real_mem, currentHeapBlock, 
            currentHeapBlock_size, dynamic_top
        );
        checkpoint_memory(ins_count, real_mem);
        checkpoint_register(ins_count, regis_0, &PC, &HI, &LO);
        ins_count++;
    }
}

void callInstruction(
    S currentInsStr, ui32 *regis_0, ui32 &HI, ui32 &LO, ui32 &PC, 
    std::ifstream & f_in, std::ofstream & f_out, void* real_mem, ui32 &currentHeapBlock, 
    ui32 &currentHeapBlock_size, ui32 &dynamic_top
){
    S _opcode = currentInsStr.substr(0,6);
    if(_opcode == "000000"){
        S _rs = currentInsStr.substr(6,5);
        S _rt = currentInsStr.substr(11,5);
        S _rd = currentInsStr.substr(16,5);
        S _sa = currentInsStr.substr(21,5);
        S _function = currentInsStr.substr(26,6);
        callRInstruction(
            _rs, _rt, _rd, _sa, _function, regis_0, HI, LO, PC, f_in, 
            f_out, real_mem, currentHeapBlock, currentHeapBlock_size, dynamic_top
        );
    }
    else if (_opcode.substr(0,5) != "00001" and _opcode.substr(0,4) != "0100"){
        S _rs = currentInsStr.substr(6,5);
        S _rt = currentInsStr.substr(11,5);
        S _immediate = currentInsStr.substr(16,16);
        callIInstruction(_opcode, _rs, _rt, _immediate, regis_0, real_mem, PC);
    }
    else if (_opcode.substr(0,5) == "00001"){
        S _target = currentInsStr.substr(6,26);
        callJInstruction(_opcode, _target, PC, regis_0);
    }
    else {
        std::cout << "<simulation> Invalid instruction: " << currentInsStr << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        exit(0);
    }
}

instruction_t getInstruction(mem_t currentPC, void* real_mem){
    // local variable initialization is a must
    instruction_t tmp = 0;

    void* pos = getRealMem(currentPC, real_mem);
    memcpy(&tmp, pos, sizeof(tmp));
    return tmp;
}

int main(int argc, char* argv[]){
    u_int32_t* regis_0 = new u_int32_t[32];
    regis_0[0] = 0;
    u_int32_t PC=0x400000, LO=0, HI=0;
    void* real_mem = malloc(0x600000); //                      free() not exists
    mem_t fp = 0xA00000;
    mem_t sp = 0xA00000;
    mem_t gp = 0x508000;
    std::ifstream f_in;
    std::ofstream f_out;
    u_int32_t currentHeapBlock, currentHeapBlock_size, dynamic_top;
    memset(regis_0,0,sizeof(ui32)*32);
    memset(real_mem,0,0x600000);

    f_out.open(argv[5]);

    f_in.open(argv[4]);
    if (!f_in.is_open()){
        std::cout << "Inputs file cannot be found. Please check file path.";
        exit(0);
    }

    if(argc != 6){
        std::cout << "Wrong Input." << "\ncurrent argc: " << argc;
        exit(0);
    }
    
    simulation(
        argv[1], argv[2], argv[3], argv[4], argv[5], 
        regis_0, PC, LO, HI, real_mem, fp, sp, gp, 
        f_in, f_out, 
        currentHeapBlock, currentHeapBlock_size, dynamic_top);
    free(real_mem);
    return 0;
}