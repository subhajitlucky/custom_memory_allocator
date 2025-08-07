// include/allocator.hpp  
// Step 4: Memory Pool with my_malloc and my_free

#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>

class MemoryPool {
private:
    void* memory_start;
    size_t pool_size;

    struct BlockHeader {
        size_t size;
        bool is_free;
        BlockHeader* next;
    };

    BlockHeader* head;

public:
    MemoryPool(size_t size);
    ~MemoryPool();
    void* getPoolStart();
    size_t getPoolSize();
    void printBlocks();
    void* my_malloc(size_t size);    // Step 3: Our malloc implementation
    void my_free(void* ptr);         // Step 4: Our free implementation
};

#endif
