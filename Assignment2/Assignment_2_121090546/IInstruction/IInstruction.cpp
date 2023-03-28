#include "IInstruction.hpp"

#include "../conversion.hpp"

#include <string.h>

#include <iostream>
#include <unordered_map>
S I_opcode, I_rs, I_rt, immediate;
unsigned long I_OPCODE, I_RS, I_RT;
immediate_t IMMEDIATE;

typedef u_int32_t ui32;

static std::unordered_map<S, S> R_funct{

    {"add", "100000"}, 
    {"addu", "100001"}, 
    {"and", "100100"}, 
    {"div", "011010"}, 
    {"divu", "011011"},
    {"jalr", "001001"}, 
    {"jr", "001000"}, 
    {"mfhi", "010000"}, 
    {"mflo", "010010"}, 
    {"mthi", "010001"},
    {"mtlo", "010011"}, 
    {"mult", "011000"}, 
    {"multu", "011001"}, 
    {"nor", "100111"}, 
    {"or", "100101"},
    {"sll", "000000"}, 
    {"sllv", "000100"}, 
    {"slt", "101010"}, 
    {"sltu", "101011"}, 
    {"sra", "000011"},
    {"srav", "000111"}, 
    {"srl", "000010"}, 
    {"srlv", "000110"}, 
    {"sub", "100010"}, 
    {"subu", "100011"},
    {"syscall", "001100"}, 
    {"xor", "100110"}

};

static std::unordered_map<S, S> I_opcd {

    {"addi", "001000"}, 
    {"addiu", "001001"}, 
    {"andi", "001100"}, 
    {"beq", "000100"}, 
    {"bgez", "000001"},
    {"bgtz", "000111"}, 
    {"blez", "000110"}, 
    {"bltz", "000001"}, 
    {"bne", "000101"},
    {"lb", "100000"}, 
    {"lbu", "100100"}, 
    {"lh", "100001"}, 
    {"lhu", "100101"}, 
    {"lui", "001111"},
    {"lw", "100011"}, 
    {"ori", "001101"}, 
    {"sb", "101000"}, 
    {"slti", "001010"}, 
    {"sltiu", "001011"}, 
    {"sh", "101001"}, 
    {"sw", "101011"}, 
    {"xori", "001110"}, 
    {"lwl", "100010"},
    {"lwr", "100110"}, 
    {"swl", "101010"},
    {"swr", "101110"}
};

static std::unordered_map<S, S> J_opcd{

    {"j", "000010"}, {"jal", "000011"}

};

static std::unordered_map<S, S> rt_notes {
    {"bgez", "00001"},
    {"bgtz", "00000"},
    {"blez", "00000"},
    {"bltz", "00000"},
};


void callIInstruction(
    S _I_opcode,
    S _rs,
    S _rt,
    S _immediate,
    u_int32_t* regis_0,
    void* real_mem,
    ui32 & PC
) {
    I_opcode = _I_opcode;
    I_rs = _rs;
    I_rt = _rt;
    immediate = _immediate;
    I_OPCODE = binstrToUL(I_opcode);
    I_RS = binstrToUL(I_rs);
    I_RT = binstrToUL(I_rt);
    IMMEDIATE = binstrTo16uint(immediate);
    
    if (I_opcode == I_opcd["addi"]){
        addi(regis_0);
    }
    else if(I_opcode == I_opcd["addiu"]){
        addiu(regis_0);
    }
    else if(I_opcode == I_opcd["andi"]){
        andi(regis_0);        
    }
    else if(I_opcode == I_opcd["beq"]){
        beq(regis_0, PC);
    }
    else if(I_opcode == I_opcd["bgez"]){
        if (I_rt == rt_notes["bgez"]){
            bgez(regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bgez: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bgtz"]){
        if (I_rt == rt_notes["bgtz"]){
            bgtz(regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bgtz: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["blez"]){
        if (I_rt == rt_notes["blez"]){
            blez(regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of blez: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bltz"]){
        if (I_rt == rt_notes["bltz"]){
            bltz(regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bltz: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bne"]){
        bne(regis_0, PC);
    }
    else if(I_opcode == I_opcd["lb"]){
        lb(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lbu"]){
        lbu(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lh"]){
        lh(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lhu"]){
        lhu(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lui"]){
        lui(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lw"]){
        lw(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["ori"]){
        ori(regis_0);
    }
    else if(I_opcode == I_opcd["sb"]){
        sb(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["slti"]){
        slti(regis_0);
    }
    else if(I_opcode == I_opcd["sltiu"]){
        sltiu(regis_0);
    }
    else if(I_opcode == I_opcd["sh"]){
        sh(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["sw"]){
        sw(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["xori"]){
        xori(regis_0);
    }
    else if(I_opcode == I_opcd["lwl"]){
        lwl(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lwr"]){
        lwr(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["swl"]){
        swl(regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["swr"]){
        swr(regis_0, real_mem);
    }
    else {
        std::cout << "<callIInstruction> invalid I_opcode: " << I_opcode << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        exit(0);
    }
}

void addi(ui32* regis_0){
    *(regis_0 + I_RT) = int32_t(*(regis_0 + I_RS)) + int32_t(IMMEDIATE);
}
void addiu(ui32* regis_0){
    *(regis_0 + I_RT) = int32_t(*(regis_0 + I_RS)) + int32_t(IMMEDIATE);
}
void andi(ui32* regis_0){
    *(regis_0 + I_RT) = int32_t(*(regis_0 + I_RS)) & int32_t(IMMEDIATE);
}
void beq(ui32* regis_0, ui32& PC){
    if (*(regis_0 + I_RS) == *(regis_0 + I_RT)){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void bgez(ui32* regis_0, ui32& PC){
    if (int32_t(*(regis_0 + I_RS)) >= 0){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void bgtz(ui32* regis_0, ui32& PC){
    if (int32_t(*(regis_0 + I_RS)) > 0){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void blez(ui32* regis_0, ui32& PC){
    if (int32_t(*(regis_0 + I_RS)) <= 0){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void bltz(ui32* regis_0, ui32& PC){
    if (int32_t(*(regis_0 + I_RS)) < 0){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void bne(ui32* regis_0, ui32& PC){
    if (*(regis_0 + I_RS) != *(regis_0 + I_RT)){
        PC = PC + (int32_t(IMMEDIATE) << 2);
    }
}
void lb(ui32* regis_0, void* real_mem){
    int8_t byte;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    memcpy(&byte, pos, sizeof(byte));
    *(regis_0 + I_RT) = int32_t(byte);
}
void lbu(ui32* regis_0, void* real_mem){
    u_int8_t byte;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    memcpy(&byte, pos, sizeof(byte));
    *(regis_0 + I_RT) = u_int32_t(byte);
}
void lh(ui32* regis_0, void* real_mem){
    int16_t half;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    memcpy(&half, pos, sizeof(half));
    *(regis_0 + I_RT) = int32_t(half);
}
void lhu(ui32* regis_0, void* real_mem){
    u_int16_t half;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    memcpy(&half, pos, sizeof(half));
    *(regis_0 + I_RT) = int32_t(half);
}
void lui(ui32* regis_0, void* real_mem){
    *(regis_0 + I_RT) = u_int32_t(IMMEDIATE) << 16;
}
void lw(ui32* regis_0, void* real_mem){
    u_int32_t word;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    memcpy(&word, pos, sizeof(word));
    *(regis_0 + I_RT) = word;
}
void ori(ui32* regis_0){
    *(regis_0 + I_RT) = *(regis_0 + I_RS) | u_int32_t(IMMEDIATE);
}
void sb(ui32* regis_0, void* real_mem){
    u_int8_t byte;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b8 bs(*(regis_0 + I_RT));
    byte = bs.to_ulong();
    memcpy(pos, &byte, sizeof(byte));
}
void slti(ui32* regis_0){
    *(regis_0 + I_RT) = (int32_t(*(regis_0 + I_RS)) < int32_t(IMMEDIATE));
}
void sltiu(ui32* regis_0){
    *(regis_0 + I_RT) = (*(regis_0 + I_RS) < u_int32_t(IMMEDIATE));
}
void sh(ui32* regis_0, void* real_mem){
    u_int16_t half;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b16 bs(*(regis_0 + I_RT));
    half = bs.to_ulong();
    memcpy(pos, &half, sizeof(half));
}
void sw(ui32* regis_0, void* real_mem){
    u_int32_t word;
    void* pos = getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b32 bs(*(regis_0 + I_RT));
    word = bs.to_ulong();
    memcpy(pos, &word, sizeof(word));
}
void xori(ui32* regis_0){
    *(regis_0 + I_RT) = (*(regis_0 + I_RS) xor u_int32_t(IMMEDIATE));
}
void lwl(ui32* regis_0, void* real_mem){
    size_t size = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    void* regis_pos = regis_0 + I_RT;
    void* mem_pos = getRealMem((*(regis_0 + I_RS) + int32_t(IMMEDIATE)), real_mem);
    memcpy(regis_pos, mem_pos, size);
}
void lwr(ui32* regis_0, void* real_mem){
    size_t size = (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    void* regis_pos = (u_int8_t*)(regis_0 + I_RT) + 4 - size;
    void* mem_pos = getRealMem((*(regis_0 + I_RS) + int32_t(IMMEDIATE)) - size, real_mem);
    memcpy(regis_pos, mem_pos, size);
}
void swr(ui32* regis_0, void* real_mem){
    size_t size = (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    void* regis_pos = (u_int8_t*)(regis_0 + I_RT) + 4 - size;
    void* mem_pos = getRealMem((*(regis_0 + I_RS) + int32_t(IMMEDIATE)) - size, real_mem);
    memcpy(mem_pos, regis_pos, size);
}
void swl(ui32* regis_0, void* real_mem){
    size_t size = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    void* regis_pos = regis_0 + I_RT;
    void* mem_pos = getRealMem((*(regis_0 + I_RS) + int32_t(IMMEDIATE)), real_mem);
    memcpy(mem_pos, regis_pos, size);
}

