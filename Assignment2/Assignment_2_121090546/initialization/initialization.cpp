#include "initialization.hpp"
#include "../conversion.hpp"

#include <string.h>

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <iostream>

typedef u_int32_t ui32;
typedef std::string S;

static std::unordered_map<std::string, int> registerNum {

    {"$zero", 0}, 
    {"$at", 1}, 
    {"$v0", 2}, {"$v1", 3}, 
    {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11}, {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19}, {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, 
    {"$k0", 26}, {"$k1", 27}, 
    {"$gp", 28}, 
    {"$sp", 29}, 
    {"$fp", 30}, 
    {"$ra", 31}

};

void initialization(
    S asmSourceFile, 
    S assembledBinCodesFile, 
    S checkpointsFile, 
    S inputsFile,
    void* real_mem,
    ui32* regis_0,
    ui32 & PC,
    ui32 & gp,
    ui32 & sp,
    ui32 & fp,
    std::ifstream & f_in,
    std::ofstream & f_out,
    ui32 & dynamic_top
){
    // allocate memory
    
    // set default values
    PC = 0x400000;
    *(regis_0 + registerNum["$gp"]) = gp;
    *(regis_0 + registerNum["$sp"]) = sp;
    *(regis_0 + registerNum["$fp"]) = fp;
    

    // read necessities
    readDataSection(asmSourceFile, dynamic_top, real_mem);
    readInstructions(assembledBinCodesFile, real_mem);
    
}

void readInstructions(S assembledBinCodesFile, void* real_mem){
    mem_t memCount = 0x400000;
    void* unaligned_int_ptr;
    std::ifstream bin_in(assembledBinCodesFile);

    if (!bin_in.is_open()){
        std::cout << "Assembled binary code file cannot be found. Please check file path.";
        exit(0);
    }

    std::string line;
    u_int32_t tmp;
    while(getline(bin_in, line)){
        unaligned_int_ptr = (void* )getRealMem(memCount, real_mem);
        tmp = binstrTo32uint(line.c_str());

        memcpy(unaligned_int_ptr, &tmp, sizeof(tmp));
        memCount += 4;
    }
}

void readDataSection(S asmSourceFile, ui32 & dynamic_top, void* real_mem){
    mem_t dataCount = 0x500000;
    std::ifstream asm_in(asmSourceFile);

    if (!asm_in.is_open()){
        std::cout << "asm source file cannot be found. Please check file path.";
        exit(0);
    }

    S line;
    S subLine, token;
    std::istringstream is;
    int comment;
    while(getline(asm_in, line)){
        comment = line.find('#');
        if(comment != line.npos){
            subLine = line.substr(0,comment);
        }
        else {
            subLine = line;
        }
        if(subLine.find(".data") != subLine.npos){
            break;
        }
    }

    while(getline(asm_in, line)){
        if(line.find(".text") != line.npos) break;
        comment = line.find('#');
        if(comment != line.npos){
            subLine = line.substr(0,comment);
        }
        else {
            subLine = line;
        }
        if(subLine.empty()) continue;
        
        std::istringstream is(subLine);
        is >> std::skipws >> token;
        is >> std::skipws >> token;
        if(token == ".ascii"){
            S s;
            is >> std::skipws >> s;
            s = s.substr(1, s.length()-2);
            dataCount = read_ascii(dataCount, s, real_mem);
        }
        else if(token == ".asciiz"){
            S s;
            is >> std::skipws >> s;
            s = s.substr(1, s.length()-2);
            dataCount = read_ascii(dataCount, s, real_mem);
        }
        else if(token == ".word"){
            int32_t i;
            is >> std::skipws >> i;
            dataCount = read_word(dataCount, i, real_mem);
        }
        else if(token == ".byte"){
            S s;
            std::vector<int8_t> v;
            is >> std::skipws >> s;
            std::replace(s.begin(), s.end(), ',', ' ');
            std::istringstream tmps(s);
            int8_t tmpi;
            while(!tmps.eof()){
                tmps >> tmpi;
                v.push_back(tmpi);
            }
            dataCount = read_byte(dataCount, v, real_mem);
        }
        else if(token == ".half"){
            S s;
            std::vector<int16_t> v;
            is >> std::skipws >> s;
            std::replace(s.begin(), s.end(), ',', ' ');
            std::istringstream tmps(s);
            int16_t tmpi;
            while(!tmps.eof()){
                tmps >> tmpi;
                v.push_back(tmpi);
            }
            dataCount = read_half(dataCount, v, real_mem);
        }
    }
    dynamic_top = dataCount;
}

mem_t read_ascii(mem_t mem, S s, void* real_mem){
    char* pos = (char*)getRealMem(mem, real_mem);
    int len = s.length();
    for(int i=0;i<len;i++){
        if(s[i] == '\\'){
            if(s.substr(i, 2) == "\\n"){
                *pos = '\n';
            }
            else if(s.substr(i, 2) == "\\\\"){
                *pos = '\\';
            }
            else if(s.substr(i, 2) == "\\0"){
                *pos = '\0';
            }
            pos += 2;
            i += 1;
        }
        else {
            *pos = s[i];
            pos += 1;
        }
    }
    if (len%4 != 0){
        pos += 4 - len%4;
    }
    return mem_t((unsigned long)(pos) - (unsigned long)getRealMem(mem, real_mem)) + mem;
}

mem_t read_asciiz(mem_t mem, S s, void* real_mem){
    char* pos = (char* )getRealMem(mem, real_mem);
    int len = s.length();
    for(int i=0;i<len;i++){
        if(s[i] == '\\'){
            if(s.substr(i, 2) == "\\n"){
                *pos = '\n';
            }
            else if(s.substr(i, 2) == "\\\\"){
                *pos = '\\';
            }
            else if(s.substr(i, 2) == "\\0"){
                *pos = '\0';
            }
            pos += 2;
            i += 1;
        }
        else {
            *pos = s[i];
            pos += 1;
        }
    }
    *pos = '\0';
    *pos += 1;
    if ((len+1)%4 != 0){
        pos += 4 - (len+1)%4;
    }
    return mem_t((unsigned long)(pos) - (unsigned long)getRealMem(mem, real_mem)) + mem;
}

mem_t read_word(mem_t mem, int32_t x, void* real_mem){
    int32_t tmp = x;
    void* pos = getRealMem(mem, real_mem);
    memcpy(pos, &tmp, sizeof(tmp));
    return 4 + mem;
}

mem_t read_half(mem_t mem, std::vector<int16_t> v, void* real_mem){
    int16_t tmp;
    mem_t memCount = mem;
    void* pos;
    for(int i=0;i<=v.size();i++){
        pos = getRealMem(mem, real_mem);
        tmp = v[i];
        memcpy(pos, &tmp, sizeof(tmp));
        memCount += 2;
    }

    if(v.size()%2 != 0){
        return memCount + 2;
    }
    else return memCount;
}

mem_t read_byte(mem_t mem, std::vector<int8_t> v, void* real_mem){
    mem_t memCount = mem;
    int8_t tmp;
    void* pos = getRealMem(mem, real_mem);
    for(int i=0;i<=v.size();i++){
        pos = getRealMem(mem, real_mem);
        tmp = v[i];
        memcpy(pos, &tmp, sizeof(tmp));
        memCount += 1;
    }

    if(v.size()%4 != 0){
        return memCount + 4 - v.size()%4;
    }
    else return memCount;
}