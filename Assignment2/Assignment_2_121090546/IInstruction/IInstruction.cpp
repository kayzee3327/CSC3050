#include "IInstruction.hpp"

#include "conversion.hpp"
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
    u_int32_t PC,
    unsigned long _real_mem
) {
    I_opcode = _I_opcode;
    I_rs = _rs;
    I_rt = _rt;
    immediate = _immediate;
    I_OPCODE = binstrToUL(I_opcode);
    I_RS = binstrToUL(I_rs);
    I_RT = binstrToUL(I_rt);
    IMMEDIATE = toBinary16uint(immediate);
    ui32* Regis_0;
    unsigned long real_mem;
    if (I_opcode == I_opcd["addi"]){
        addi(Regis_0);
    }
    else if(I_opcode == I_opcd["addiu"]){
        addiu(Regis_0);
    }
    else if(I_opcode == I_opcd["andi"]){
        andi(Regis_0);        
    }
    else if(I_opcode == I_opcd["beq"]){
        beq(Regis_0, PC);
    }
    else if(I_opcode == I_opcd["bgez"]){
        if (I_rt == rt_notes["bgez"]){
            bgez(Regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bgez: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bgtz"]){
        if (I_rt == rt_notes["bgtz"]){
            bgtz(Regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bgtz: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["blez"]){
        if (I_rt == rt_notes["blez"]){
            blez(Regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of blez: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bltz"]){
        if (I_rt == rt_notes["bltz"]){
            bltz(Regis_0, PC);
        }
        else {
            std::cout << "<callIInstruction> Invalid I_rt of bltz: " << I_rt << std::endl;
            std::cout << "PC: " << PC << std::endl;
            exit(0);
        }
    }
    else if(I_opcode == I_opcd["bne"]){
        bne(Regis_0, PC);
    }
    else if(I_opcode == I_opcd["lb"]){
        lb(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lbu"]){
        lbu(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lh"]){
        lh(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lhu"]){
        lhu(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lui"]){
        lui(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lw"]){
        lw(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["ori"]){
        ori(Regis_0);
    }
    else if(I_opcode == I_opcd["sb"]){
        sb(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["slti"]){
        slti(Regis_0);
    }
    else if(I_opcode == I_opcd["sltiu"]){
        sltiu(Regis_0);
    }
    else if(I_opcode == I_opcd["sh"]){
        sh(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["sw"]){
        sw(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["xori"]){
        xori(Regis_0);
    }
    else if(I_opcode == I_opcd["lwl"]){
        lwl(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["lwr"]){
        lwr(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["swl"]){
        swl(Regis_0, real_mem);
    }
    else if(I_opcode == I_opcd["swr"]){
        swr(Regis_0, real_mem);
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
void lb(ui32* regis_0, unsigned long real_mem){
    int8_t byte;
    int8_t* pos = (int8_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    byte = *pos;
    *(regis_0 + I_RT) = int32_t(byte);
}
void lbu(ui32* regis_0, unsigned long real_mem){
    u_int8_t byte;
    u_int8_t* pos = (u_int8_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    byte = *pos;
    *(regis_0 + I_RT) = u_int32_t(byte);
}
void lh(ui32* regis_0, unsigned long real_mem){
    int16_t half;
    int16_t* pos = (int16_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    half = *pos;
    *(regis_0 + I_RT) = int32_t(half);
}
void lhu(ui32* regis_0, unsigned long real_mem){
    u_int16_t half;
    u_int16_t* pos = (u_int16_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    half = *pos;
    *(regis_0 + I_RT) = int32_t(half);
}
void lui(ui32* regis_0, unsigned long real_mem){
    *(regis_0 + I_RT) = u_int32_t(IMMEDIATE) << 16;
}
void lw(ui32* regis_0, unsigned long real_mem){
    data_t* pos = (data_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    *(regis_0 + I_RT) = *pos;
}
void ori(ui32* regis_0){
    *(regis_0 + I_RT) = *(regis_0 + I_RS) | u_int32_t(IMMEDIATE);
}
void sb(ui32* regis_0, unsigned long real_mem){
    u_int8_t* pos = (u_int8_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b8 bs(*(regis_0 + I_RT));
    *pos = bs.to_ulong();
}
void slti(ui32* regis_0){
    *(regis_0 + I_RT) = (int32_t(*(regis_0 + I_RS)) < int32_t(IMMEDIATE));
}
void sltiu(ui32* regis_0){
    *(regis_0 + I_RT) = (*(regis_0 + I_RS) < u_int32_t(IMMEDIATE));
}
void sh(ui32* regis_0, unsigned long real_mem){
    u_int16_t* pos = (u_int16_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b16 bs(*(regis_0 + I_RT));
    *pos = bs.to_ulong();
}
void sw(ui32* regis_0, unsigned long real_mem){
    u_int32_t* pos = (u_int32_t*)getRealMem(*(regis_0 + I_RS) + int32_t(IMMEDIATE), real_mem);
    b32 bs(*(regis_0 + I_RT));
    *pos = bs.to_ulong();
}
void xori(ui32* regis_0){
    *(regis_0 + I_RT) = (*(regis_0 + I_RS) xor u_int32_t(IMMEDIATE));
}
void lwl(ui32* regis_0, unsigned long real_mem){
    int count = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    mem_t memor;
    unsigned long regis = (unsigned long)(regis_0 + I_RT);
    for (int i=0;i<count;i++){
        memor = *(regis_0 + I_RS) + int32_t(IMMEDIATE) + mem_t(i);
        regis = regis + (long long)(i);
        *(u_int8_t*)regis = *(u_int8_t*)getRealMem(memor, real_mem);
    }
}
void lwr(ui32* regis_0, unsigned long real_mem){
    int count = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    mem_t memor;
    unsigned long regis = (unsigned long)(regis_0 + I_RT);
    for (int i=0;i<count;i++){
        memor = *(regis_0 + I_RS) + int32_t(IMMEDIATE) - mem_t(i);
        regis = regis - (long long)(i);
        *(u_int8_t*)regis = *(u_int8_t*)getRealMem(memor, real_mem);
    }
}
void swr(ui32* regis_0, unsigned long real_mem){
    int count = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    mem_t memor;
    unsigned long regis = (unsigned long)(regis_0 + I_RT);
    for (int i=0;i<count;i++){
        memor = *(regis_0 + I_RS) + int32_t(IMMEDIATE) - mem_t(i);
        regis = regis - (long long)(i);
        *(u_int8_t*)getRealMem(memor, real_mem) = *(u_int8_t*)regis;
    }
}
void swl(ui32* regis_0, unsigned long real_mem){
    int count = 4 - (*(regis_0 + I_RS) + int32_t(IMMEDIATE)) % 4;
    mem_t memor;
    unsigned long regis = (unsigned long)(regis_0 + I_RT);
    for (int i=0;i<count;i++){
        memor = *(regis_0 + I_RS) + int32_t(IMMEDIATE) + mem_t(i);
        regis = regis + (long long)(i);
        *(u_int8_t*)getRealMem(memor, real_mem) = *(u_int8_t*)regis;
    }
}

