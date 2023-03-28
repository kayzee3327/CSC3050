#include "Syscall.hpp"
#include "../conversion.hpp"

#include <iostream>
#include <fstream>

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void syscall(
    ui32* regis_0, ui32 & PC, 
    std::ifstream & f_in, std::ofstream & f_out, 
    void* real_mem, 
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

void print_int(std::ofstream & f_out, ui32* regis_0){
    int tmp = regis_0[4];
    f_out << tmp << std::endl;
}
void print_string(std::ofstream & f_out, ui32* regis_0, void* real_mem){
    char* pos = (char*)getRealMem(*(regis_0 + 4), real_mem);
    std::string tmp(pos);
    f_out << tmp << std::endl;
}
void read_int(std::ifstream & f_in, ui32* regis_0){
    int32_t tmp;
    f_in >> tmp;
    regis_0[2] = tmp;
}
void read_string(std::ifstream & f_in, ui32* regis_0, void* real_mem){
    char* pos = (char*)getRealMem(*(regis_0 + 4), real_mem);
    S tmp;
    f_in >> std::skipws >> tmp;
    strcpy(pos, tmp.c_str());
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
void print_char(std::ofstream & f_out, ui32* regis_0){
    char tmp = regis_0[4];
    f_out << tmp << std::endl;
}
void read_char(std::ifstream & f_in, ui32* regis_0){
    char tmp;
    f_in >> tmp;
    *(regis_0 + 2) = tmp;
}
void open(ui32* regis_0, void* real_mem){
    char* file_ptr = (char*)getRealMem(*(regis_0 + 4), real_mem);
    *(regis_0 + 4) = open(file_ptr, *(regis_0 + 5), *(regis_0 + 6));
}
void read(ui32* regis_0, void* real_mem){
    char* buffer = (char*)getRealMem(*(regis_0 + 5), real_mem);
    *(regis_0 + 4) = read(*(regis_0 + 4), buffer, *(regis_0 + 6));
}
void write(ui32* regis_0, void* real_mem){
    char* buffer = (char*)getRealMem(*(regis_0 + 5), real_mem);
    *(regis_0 + 4) = write(*(regis_0 + 4), buffer, *(regis_0 + 6));
}
void close(ui32* regis_0){
    close(*(regis_0 + 4));
}
void exit2(ui32* regis_0){
    exit(*(regis_0 + 4));
}
