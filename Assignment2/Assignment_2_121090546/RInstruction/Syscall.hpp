#ifndef _SYSCALL
#define _SYSCALL

#include <stdlib.h>
#include <string>
#include <cstdio>

typedef u_int32_t ui32;
typedef std::string S;

void syscall(
    ui32* regis_0, ui32 & PC, 
    std::ifstream & f_in, std::ofstream & f_out, 
    void* real_mem, 
    ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, ui32 & dynamic_top
);

void print_int(std::ofstream & f_out, ui32* regis_0);
void print_string(std::ofstream & f_out, ui32* regis_0, void* real_mem);
void read_int(std::ifstream & f_in, ui32* regis_0);
void read_string(std::ifstream & f_in, ui32* regis_0, void* real_mem);
void sbrk(ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, 
    ui32 & dynamic_top, ui32* regis_0);
void exit1();
void print_char(std::ofstream & f_out, ui32* regis_0);
void read_char(std::ifstream & f_in, ui32* regis_0);
void open(ui32* regis_0, void* real_mem);
void read(ui32* regis_0, void* real_mem);
void write(ui32* regis_0, void* real_mem);
void close(ui32* regis_0);
void exit2(ui32* regis_0);







#endif