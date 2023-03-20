#include "initialization.hpp"

#include <string.h>

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
std::unordered_map<std::string, int> registerNum = {
    
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

std::string toBinary(u_int32_t x){
    std::bitset<32> bs(x);
    return bs.to_string();
}
instruction_t toBinary(std::string s){
    std::bitset<32> bs(s);
    return bs.to_ulong();
}

void initialization(std::string asmSourceFile, std::string assembledBinCodesFile){
    // apply memory

    real_mem = malloc(0x600000);
    PC = 0x400000;

    // set default values

    memset(registers,0,sizeof(register_t)*32);
    registers[registerNum["$gp"]] = gp;
    registers[registerNum["$sp"]] = sp;
    registers[registerNum["$fp"]] = fp;

    // read necessities

    readDataSection(asmSourceFile);
    readInstructions(assembledBinCodesFile);
}

void readInstructions(std::string assembledBinCodesFile){
    instruction_t* insCount = (instruction_t* )getRealMem(0x400000);
    std::ifstream bin_in(assembledBinCodesFile);
    std::string line;
    while(getline(bin_in, line)){
        *insCount = toBinary(line);
        insCount += 4;
    }
}

void readDataSection(std::string asmSourceFile){
    mem_t dataCount = 0x500000;
    std::ifstream asm_in(asmSourceFile);
    std::string line;
    std::string subLine, token;
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
        if(token == ".ascii"){
            std::string s;
            is >> std::skipws >> s;
            s = s.substr(1, s.length()-2);
            dataCount = read_ascii(dataCount, s);
        }
        else if(token == ".asciiz"){
            std::string s;
            is >> std::skipws >> s;
            s = s.substr(1, s.length()-2);
            dataCount = read_ascii(dataCount, s);
        }
        else if(token == ".word"){
            int32_t i;
            is >> std::skipws >> i;
            dataCount = read_word(dataCount, i);
        }
        else if(token == ".byte"){
            std::string s;
            std::vector<int8_t> v;
            is >> std::skipws >> s;
            std::replace(s.begin(), s.end(), ',', ' ');
            std::istringstream tmps(s);
            int8_t tmpi;
            while(!tmps.eof()){
                tmps >> tmpi;
                v.push_back(tmpi);
            }
            dataCount = read_byte(dataCount, v);
        }
        else if(token == ".half"){
            std::string s;
            std::vector<int16_t> v;
            is >> std::skipws >> s;
            std::replace(s.begin(), s.end(), ',', ' ');
            std::istringstream tmps(s);
            int16_t tmpi;
            while(!tmps.eof()){
                tmps >> tmpi;
                v.push_back(tmpi);
            }
            dataCount = read_half(dataCount, v);
        }
    }
}

mem_t read_ascii(mem_t mem, std::string s){
    char* pos = (char* )getRealMem(mem);
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
    return mem_t((pos) - getRealMem(mem)) + mem;
}

mem_t read_asciiz(mem_t mem, std::string s){
    char* pos = (char* )getRealMem(mem);
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
    return mem_t((pos) - getRealMem(mem)) + mem;
}

mem_t read_word(mem_t mem, int32_t x){
    int32_t* pos = (int32_t* )getRealMem(mem);
    *pos = x;
    return 4 + mem;
}

mem_t read_half(mem_t mem, std::vector<int16_t> v){
    int16_t* pos = (int16_t* )getRealMem(mem);
    for(int i=0;i<=v.size();i++){
        *pos = v[i];
        pos += 2;
    }

    if(v.size()%2 != 0){
        return mem_t(pos - getRealMem(mem)) + mem + 2;
    }
    else return mem_t(pos - getRealMem(mem)) + mem;
}

mem_t read_byte(mem_t mem, std::vector<int8_t> v){
    int8_t* pos = (int8_t* )getRealMem(mem);
    for(int i=0;i<=v.size();i++){
        *pos = v[i];
        pos += 1;
    }

    if(v.size()%4 != 0){
        return mem_t(pos - getRealMem(mem)) + mem + 4-v.size()%4;
    }
    else return mem_t(pos - getRealMem(mem)) + mem;
}