#ifndef _SYSCALL
#define _SYSCALL

#include <stdlib.h>
#include <string>
#include <cstdio>

typedef u_int32_t ui32;
typedef std::string S;

void syscall(
    ui32* regis_0, ui32 & PC, 
    FILE* f_in, FILE* f_out, 
    unsigned long real_mem, 
    ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, ui32 & dynamic_top
);

void print_int(FILE* f_out, ui32* regis_0);
void print_string(FILE* f_out, ui32* regis_0, unsigned long real_mem);
void read_int(FILE* f_in, ui32* regis_0);
void read_string(FILE* f_in, ui32* regis_0, unsigned long real_mem);
void sbrk(ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, 
    ui32 & dynamic_top, ui32* regis_0);
void exit1();
void print_char(FILE* f_out, ui32* regis_0);
void read_char(FILE* f_in, ui32* regis_0);
void open(ui32* regis_0, unsigned long real_mem);
void read(ui32* regis_0, unsigned long real_mem);
void write(ui32* regis_0, unsigned long real_mem);
void close(ui32* regis_0);
void exit2(ui32* regis_0);







#endif