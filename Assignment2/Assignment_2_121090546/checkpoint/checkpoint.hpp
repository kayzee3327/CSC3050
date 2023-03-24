#ifndef _CHECKPOINT
#define _CHECKPOINT

#include <set>
#include <string>

void init_checkpoints(std::string checkpointsFile);
void checkpoint_memory(int ins_count, void* mem_start);
void checkpoint_register(int ins_count, u_int32_t* regis_0);

#endif