// src/allocator.cpp
#include "allocator.hpp"

MemoryPool::MemoryPool(size_t size) {
    pool_size = size;
    memory_start = std::malloc(pool_size);

    if (!memory_start) {
        std::cerr << "ERROR: Failed to allocate memory pool\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Memory Pool created: " << pool_size << " bytes at " << memory_start << std::endl;
}

MemoryPool::~MemoryPool() {
    std::free(memory_start);
    std::cout << "Memory Pool destroyed.\n";
}

void* MemoryPool::getPoolStart() {
    return memory_start;
}

size_t MemoryPool::getPoolSize() {
    return pool_size;
}
