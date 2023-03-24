#include "checkpoint.hpp"

#include <set>
#include <cstdio>
// checkpoint
std::set<int> checkpoints;
void init_checkpoints(char* checkpoint_file) {
    FILE *fp = fopen(checkpoint_file, "r");
    int tmp, i = 0;
    while(fscanf(fp, "%d", &tmp) != EOF){
        checkpoints.insert(tmp);
    }
}
void checkpoint_memory(int ins_count, void* mem_start) {
    if (!checkpoints.count(ins_count))
        return;
    std::string name = "memory_" + std::to_string(ins_count) + ".bin";
    FILE * fp = fopen(name.c_str(), "wb");
    fwrite(mem_start, 1, 0x600000, fp);
    fclose(fp);
}
void checkpoint_register(int ins_count, u_int32_t* regis_0, u_int32_t* pc, u_int32_t* hi, u_int32_t* lo) {
    if (!checkpoints.count(ins_count))
        return;
    std::string name = "register_" + std::to_string(ins_count) + ".bin";
    FILE * fp = fopen(name.c_str(), "wb");
    for(int i=0;i<32;i++){
        fwrite(regis_0+i, 4, 1, fp);
    }
    fwrite(pc, 4, 1, fp);
    fwrite(hi, 4, 1, fp);
    fwrite(lo, 4, 1, fp);
    fclose(fp);
}
