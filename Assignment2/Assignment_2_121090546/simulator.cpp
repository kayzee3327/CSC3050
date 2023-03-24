#include "simulation.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    u_int32_t* regis_0;
    u_int32_t PC, LO, HI;
    void* real_mem; //                      free() not exists
    mem_t fp = 0xA00000;
    mem_t sp = 0xA00000;
    mem_t gp = 0x508000;
    FILE *f_in, *f_out;
    u_int32_t currentHeapBlock, currentHeapBlock_size, dynamic_top;
    if(argc != 5){
        cout << "Wrong Input.";
        exit(0);
    }
    simulation(
        argv[0], argv[1], argv[2], argv[3], argv[4], 
        regis_0, PC, LO, HI, real_mem, fp, sp, gp, 
        f_in, f_out, 
        currentHeapBlock, currentHeapBlock_size, dynamic_top);
    return 0;
}