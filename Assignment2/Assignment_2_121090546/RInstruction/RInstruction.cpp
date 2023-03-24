#include "RInstruction.hpp"
#include "conversion.hpp"

#include <iostream>
#include <unordered_map>
#include <string>

typedef std::string S;
static std::unordered_map<S, S> R_funct {

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

void callRInstruction(
    S _rs,
    S _rt,
    S _rd,
    S _sa,
    S _function,
    ui32* regis_0,
    ui32 & HI,
    ui32 & LO,
    ui32 & PC, 
    FILE* f_in, FILE* f_out, 
    unsigned long real_mem, 
    ui32 & currentHeapBlock, ui32 & currentHeapBlock_size, ui32 & dynamic_top
) {
    R_rs = _rs;
    R_rt = _rt;
    rd = _rd;
    sa = _sa;
    function = _function;
    R_RS = binstrToUL(R_rs);
    R_RT = binstrToUL(R_rt);
    RD = binstrToUL(rd);
    SA = binstrToUL(sa);
    FUNCTION = binstrToUL(function);
    if (function == R_funct["add"]){
        add(regis_0);
    }
    else if(function == R_funct["addu"]) {
        addu(regis_0);
    }
    else if(function == R_funct["and"]) {
        _and(regis_0);
    }
    else if(function == R_funct["div"]) {
        div(regis_0, LO, HI);
    }
    else if(function == R_funct["divu"]) {
        divu(regis_0, LO, HI);
    }
    else if(function == R_funct["jalr"]) {
        jalr(regis_0, PC);
    }
    else if(function == R_funct["jr"]) {
        jr(regis_0, PC);
    }
    else if(function == R_funct["mfhi"]) {
        mfhi(regis_0, HI);
    }
    else if(function == R_funct["mflo"]) {
        mflo(regis_0, LO);
    }
    else if(function == R_funct["mthi"]) {
        mthi(regis_0, HI);
    }
    else if(function == R_funct["mtlo"]) {
        mtlo(regis_0, LO);
    }
    else if(function == R_funct["mult"]) {
        mult(regis_0, HI, LO);
    }
    else if(function == R_funct["multu"]) {
        multu(regis_0, HI, LO);
    }
    else if(function == R_funct["nor"]) {
        nor(regis_0);
    }
    else if(function == R_funct["or"]) {
        _or(regis_0);
    }
    else if(function == R_funct["sll"]) {
        sll(regis_0);
    }
    else if(function == R_funct["sllv"]) {
        sllv(regis_0);
    }
    else if(function == R_funct["slt"]) {
        slt(regis_0);
    }
    else if(function == R_funct["sltu"]) {
        sltu(regis_0);
    }
    else if(function == R_funct["sra"]) {
        sra(regis_0);
    }
    else if(function == R_funct["srav"]) {
        srav(regis_0);
    }
    else if(function == R_funct["srl"]) {
        srl(regis_0);
    }
    else if(function == R_funct["srlv"]) {
        srlv(regis_0);
    }
    else if(function == R_funct["sub"]) {
        sub(regis_0);
    }
    else if(function == R_funct["subu"]) {
        subu(regis_0);
    }
    else if(function == R_funct["syscall"]) {
        syscall(regis_0, PC, f_in, f_out, real_mem, 
                currentHeapBlock, currentHeapBlock_size, dynamic_top);
    }
    else if(function == R_funct["xor"]) {
        _xor(regis_0);
    }
    else {
        std::cout << "<callRInstruction> invalid function code: " << function << std::endl;
        std::cout << "PC - 4: " << PC - 4;
        exit(0);
    }
}

void add(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RS) + *(regis_0 + R_RT);
}
void addu(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RS) + *(regis_0 + R_RT);
}
void _and(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RS) & *(regis_0 + R_RT);
}
void div(ui32* regis_0, ui32 & LO, ui32 & HI){
    LO = u_int32_t(*(regis_0 + R_RS) / *(regis_0 + R_RT));
    HI = u_int32_t(*(regis_0 + R_RS)%*(regis_0 + R_RT));
}
void divu(ui32* regis_0, ui32 & LO, ui32 & HI){
    div(regis_0, LO, HI);
}
void jalr(ui32* regis_0, ui32 & PC){
    *(regis_0 + RD) = PC;
    PC = *(regis_0 + R_RS);
}
void jr(ui32* regis_0, ui32 & PC){
    PC = *(regis_0 + R_RS);
}
void mfhi(ui32* regis_0, ui32 & HI){
    *(regis_0 + RD) = HI;
}
void mflo(ui32* regis_0, ui32 & LO){
    *(regis_0 + RD) = LO;
}
void mthi(ui32* regis_0, ui32 & HI){
    HI = *(regis_0 + R_RS);
}
void mtlo(ui32* regis_0, ui32 & LO){
    LO = *(regis_0 + R_RS);
}
void mult(ui32* regis_0, ui32 & HI, ui32 & LO){
    u_int64_t ans = u_int64_t(*(regis_0 + R_RS)) * u_int64_t(*(regis_0 + R_RT));
    b64 ansbs(ans);
    S ansstr = ansbs.to_string();
    b32 lo(ansstr.substr(0,32));
    b32 hi(ansstr.substr(32,32));
    HI = hi.to_ulong();
    LO = lo.to_ulong();
}
void multu(ui32* regis_0, ui32 & HI, ui32 & LO){
    mult(regis_0, HI, LO);
}
void nor(ui32* regis_0){
    *(regis_0 + RD) = ~(*(regis_0 + R_RT) | *(regis_0 + R_RS));
}
void _or(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RT) | *(regis_0 + R_RS);
}
void sll(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RT) << SA;
}
void sllv(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RT) << *(regis_0 + R_RS);
}
void slt(ui32* regis_0){
    *(regis_0 + RD) = (int32_t(*(regis_0 + R_RS)) < int32_t(*(regis_0 + R_RT)));
}
void sltu(ui32* regis_0){
    *(regis_0 + RD) = (*(regis_0 + R_RS) < *(regis_0 + R_RT));
}
void sra(ui32* regis_0){
    *(regis_0 + RD) = int32_t(*(regis_0 + R_RT)) >> SA;
}
void srav(ui32* regis_0){
    *(regis_0 + RD) = int32_t(*(regis_0 + R_RT)) >> *(regis_0 + R_RS);
}
void srl(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RT) << SA;
}
void srlv(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RT) << *(regis_0 + R_RS);
}
void sub(ui32* regis_0){
    *(regis_0 + RD) = int32_t(*(regis_0 + R_RS)) - int32_t(*(regis_0 + R_RT));
}
void subu(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RS) - *(regis_0 + R_RT);
}
void _xor(ui32* regis_0){
    *(regis_0 + RD) = *(regis_0 + R_RS) xor *(regis_0 + R_RT);
}