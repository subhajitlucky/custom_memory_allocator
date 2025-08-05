// include/allocator.hpp
// Step 1: Basic project setup with a simple memory pool

#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>

class MemoryPool {
private:
    void* memory_start;
    size_t pool_size;

public:
    MemoryPool(size_t size);
    ~MemoryPool();
    void* getPoolStart();
    size_t getPoolSize();
};

#endif
