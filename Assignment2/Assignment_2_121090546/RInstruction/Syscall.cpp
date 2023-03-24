#include "Syscall.hpp"
#include "conversion.hpp"

#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>

void syscall(
    ui32* regis_0, ui32 & PC, 
    FILE* f_in, FILE* f_out, 
    unsigned long real_mem, 
    ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, ui32 & dynamic_top
) {
    ui32 v0 = *(regis_0 + 2);
    switch (v0)
    {
    case 1:
        print_int(f_out, regis_0);
        break;
    case 4:
        print_string(f_out, regis_0, real_mem);
        break;
    case 5:
        read_int(f_in, regis_0);
        break;
    case 8:
        read_string(f_in, regis_0, real_mem);
        break;
    case 9:
        sbrk(currentHeapBlock, currentHeapBlock_size, dynamic_top, regis_0);
        break;
    case 10:
        exit1();
        break;
    case 11:
        print_char(f_out, regis_0);
        break;
    case 12:
        read_char(f_in, regis_0);
        break;
    case 13:
        open(regis_0, real_mem);
        break;
    case 14:
        read(regis_0, real_mem);
        break;
    case 15:
        write(regis_0, real_mem);
        break;
    case 16:
        close(regis_0);
        break;
    case 17:
        exit2(regis_0);
    default:
        std::cout << "<Syscall> Invalid syscall code: " << v0 << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        break;
    }
}

void print_int(FILE* f_out, ui32* regis_0){
    fprintf(f_out, "%d\n", *(regis_0+4));
}
void print_string(FILE* f_out, ui32* regis_0, unsigned long real_mem){
    char* pos = (char*)getRealMem(*(regis_0 + 4), real_mem);
    fprintf(f_out, "%s\n", *pos);
}
void read_int(FILE* f_in, ui32* regis_0){
    int32_t tmp;
    fscanf(f_in, "%d", &tmp);
    *(regis_0 + 2) = tmp;
}
void read_string(FILE* f_in, ui32* regis_0, unsigned long real_mem){
    char* pos = (char*)getRealMem(*(regis_0 + 4), real_mem);
    char* str;
    fgets(str, 0xFFFF, f_in);
    strcpy(pos,str);
}
void sbrk(
    ui32 & currentHeapBlock, ui32 & currenHeapBlock_size, 
    ui32 & dynamic_top, ui32* regis_0
){
    currentHeapBlock = dynamic_top;
    currenHeapBlock_size += *(regis_0 + 4);
    dynamic_top = currentHeapBlock + currenHeapBlock_size;
    *(regis_0 + 5) = currentHeapBlock;
    
}
void exit1(){
    exit(0);
}
void print_char(FILE* f_out, ui32* regis_0){
    fprintf(f_out, "%c", *(regis_0 + 4));
}
void read_char(FILE* f_in, ui32* regis_0){
    char32_t tmp;
    fscanf(f_in, "%c", &tmp);
    *(regis_0 + 2) = tmp;
}
void open(ui32* regis_0, unsigned long real_mem){
    char* file_ptr = (char*)getRealMem(*(regis_0 + 4), real_mem);
    *(regis_0 + 4) = open(file_ptr, *(regis_0 + 5), *(regis_0 + 6));
}
void read(ui32* regis_0, unsigned long real_mem){
    char* buffer = (char*)getRealMem(*(regis_0 + 5), real_mem);
    *(regis_0 + 4) = read(*(regis_0 + 4), buffer, *(regis_0 + 6));
}
void write(ui32* regis_0, unsigned long real_mem){
    char* buffer = (char*)getRealMem(*(regis_0 + 5), real_mem);
    *(regis_0 + 4) = write(*(regis_0 + 4), buffer, *(regis_0 + 6));
}
void close(ui32* regis_0){
    close(*(regis_0 + 4));
}
void exit2(ui32* regis_0){
    exit(*(regis_0 + 4));
}
