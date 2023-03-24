#include "simulation.hpp"
#include "RInstruction.hpp"
#include "JInstruction.hpp"
#include "IInstruction.hpp"
#include "simulatedRegisters.hpp"
#include "simulatedMemory.hpp"
#include "initialization.hpp"
#include "checkpoint.hpp"
#include "conversion.hpp"

#include <iostream>

void simulation(
    S asmSourceFile,
    S assembledBinCodesFile,
    S checkpointsFile,
    S inputsFile,
    S outputsFile,
    u_int32_t* regis_0, 
    u_int32_t PC, 
    u_int32_t LO, 
    u_int32_t HI,
    void* real_mem,
    mem_t fp,
    mem_t sp,
    mem_t gp,
    FILE *f_in, 
    FILE *f_out,
    u_int32_t currentHeapBlock, 
    u_int32_t currentHeapBlock_size, 
    u_int32_t dynamic_top
) {
    
    
    initialization(
        asmSourceFile, assembledBinCodesFile, checkpointsFile, inputsFile, 
        real_mem, regis_0, PC, gp, sp, fp, f_in, f_out, dynamic_top);
    init_checkpoints(checkpointsFile);
    instruction_t currentIns;
    S currentInsStr;
    int ins_count = 0;

    while(true) {
        currentIns = getInstruction(PC, (unsigned long)(real_mem));
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
            (unsigned long)(real_mem), currentHeapBlock, 
            currentHeapBlock_size, dynamic_top
        );
        ins_count++;
        // if (checkpoints.find(ins_count) != checkpoints.end()){
        //     checkpoint_memory(ins_count);
        //     checkpoint_register(ins_count);
        // }
        checkpoint_memory(ins_count, real_mem);
        checkpoint_register(ins_count, regis_0);
    }
}

void callInstruction(
    S currentInsStr, ui32 *regis_0, ui32 &HI, ui32 &LO, ui32 &PC, 
    FILE *f_in, FILE *f_out, unsigned long real_mem, ui32 &currentHeapBlock, 
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
        callIInstruction(_opcode, _rs, _rt, _immediate, regis_0, real_mem);
    }
    else if (_opcode.substr(0,5) == "00001"){
        S _target = currentInsStr.substr(6,26);
        callJInstruction(_opcode, _target, PC);
    }
    else {
        std::cout << "<simulation> Invalid instruction: " << currentInsStr << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        exit(0);
    }
}

instruction_t getInstruction(mem_t currentPC, unsigned long real_mem){
    instruction_t* pos = (instruction_t* )getRealMem(currentPC, real_mem);
    return *(pos);
}