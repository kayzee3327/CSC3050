#include "simulatedMemory.hpp"

void addData(mem_t mem, data_t data){
    data_t* p = nullptr;
    p = (data_t *)mem;
    *p = data;
}