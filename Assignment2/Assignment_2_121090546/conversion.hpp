#include <stdlib.h>

#include <bitset>

typedef u_int32_t mem_t;
typedef u_int32_t instruction_t;//  store one mips instruction
typedef std::string S;//            abbreviation of std::string
typedef std::bitset<8> b8;//        abbr.
typedef std::bitset<16> b16;//      abbr.
typedef std::bitset<32> b32;//      abbr. 
typedef std::bitset<64> b64;//      abbr.   

inline std::string toBinary32str(u_int32_t x){
    b32 bs(x);
    return bs.to_string();
}
//toBinary
inline u_int32_t binstrTo32uint(S s){
    b32 bs(s);
    return bs.to_ulong();
}
//toBinary16uint
inline u_int16_t binstrTo16uint(S s){
    b16 bs(s);
    return bs.to_ulong();
}
inline unsigned long binstrToUL(S s){
    std::bitset<5> bs(s);
    return bs.to_ulong();
}
inline void* getRealMem(mem_t mem, void* real_mem){
    u_int8_t* real_pos = (u_int8_t*)real_mem;
    real_pos = real_pos + mem - 0x400000;
    return (void*)real_pos;
}