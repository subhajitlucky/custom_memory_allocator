// include/allocator.hpp

#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>  // for size_t
#include <cstdlib>  // for malloc, free
#include <iostream>

class MemoryPool {
private:
    void* memory_start;   // Pointer to the beginning of the memory pool
    size_t pool_size;

    // NEW: Metadata for each block
    struct BlockHeader {
        size_t size;           // Size of the block (excluding header)
        bool is_free;          // Is this block free?
        BlockHeader* next;     // Pointer to the next block in the list
    };

    BlockHeader* head; // Start of block list

public:
    MemoryPool(size_t size);
    ~MemoryPool();

    void* getPoolStart(); // For debug/testing
    size_t getPoolSize();

    // NEW (for testing): Print all blocks
    void printBlocks();
    // NEW: Custom malloc implementation
    void* my_malloc(size_t size);
    // NEW: Custom free implementation
    void deallocate(void* ptr);
};

#endif
