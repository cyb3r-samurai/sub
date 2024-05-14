#pragma once

#include "RwLock.h"
#include <cstdint>

namespace SUB2 {
    class test 
    {
    public:
        RwLock lock;
        uint8_t counter;
    public:
        void read(void* shmem, void* usrmem, size_t size);
        void write(void* shmem, void* usrmem, size_t size); 
    };
    
}; 
