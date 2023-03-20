#include "simulation.hpp"
#include "RInstruction.hpp"
#include "JInstruction.hpp"
#include "IInstruction.hpp"

void simulation(
    std::string asmSourceFile,
    std::string assembledBinCodesFile,
    std::string checkpointsFile,
    std::string inputsFile,
    std::string outputsFile
) {
    initialization(asmSourceFile, assembledBinCodesFile);
    
    

}

instruction_t getInstruction(mem_t currentPC){
    instruction_t* pos = (instruction_t* )getRealMem(currentPC);
    return *(pos);
}