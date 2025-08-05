// include/allocator.hpp
// Step 2: Memory Pool with Block Metadata

#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>

class MemoryPool {
private:
    void* memory_start;
    size_t pool_size;

    // Step 2: Block metadata structure
    struct BlockHeader {
        size_t size;          // Size of user data (excluding header)
        bool is_free;         // true = available, false = in use
        BlockHeader* next;    // Pointer to next block
    };

    BlockHeader* head;        // First block in our linked list

public:
    MemoryPool(size_t size);
    ~MemoryPool();
    void* getPoolStart();
    size_t getPoolSize();
    void printBlocks();       // Step 2: Show block structure
};

#endif
