#ifndef _CHECKPOINT
#define _CHECKPOINT

#include <set>
#include <string>

void init_checkpoints(const char* checkpoint_file);
void checkpoint_memory(int ins_count, void* mem_start);
void checkpoint_register(int ins_count, u_int32_t* regis_0, u_int32_t* pc, u_int32_t* hi, u_int32_t* lo);

#endif