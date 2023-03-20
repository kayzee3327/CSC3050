#ifndef _CHECKPOINT
#define _CHECKPOINT

#include <set>
#include <string>

std::set<int> checkpoints;
void init_checkpoints(std::string checkpointsFile);
void checkpoint_memory(int ins_count);
void checkpoint_register(int ins_count);

#endif