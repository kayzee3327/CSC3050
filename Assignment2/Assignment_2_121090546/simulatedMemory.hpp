#ifndef _SIMULATED_MEMORY
#define _SIMULATED_MEMORY

#include <stdlib.h>


typedef u_int32_t mem_t; //             to store simulated address
typedef u_int32_t data_t;//             to store data of one-word size

void* real_mem; //                      free() not exists

mem_t fp = 0xA00000;
mem_t sp = 0xA00000;
mem_t gp = 0x508000;

mem_t getRealMem(mem_t mem){
    return mem - 0x400000 + mem_t(real_mem);
}
void addData(mem_t mem, data_t data);

#endif