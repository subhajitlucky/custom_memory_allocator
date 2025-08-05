// src/allocator.cpp
// Step 2: Implementation with Block Metadata
#include "allocator.hpp"

MemoryPool::MemoryPool(size_t size) {
    pool_size = size;
    memory_start = std::malloc(pool_size);

    if (!memory_start) {
        std::cerr << "ERROR: Failed to allocate memory pool\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "✅ Memory Pool created: " << pool_size << " bytes at " << memory_start << std::endl;

    // Step 2: Initialize the first block
    // The entire memory pool starts as one big free block
    
    // Cast our memory start to a BlockHeader pointer
    head = static_cast<BlockHeader*>(memory_start);
    
    // Set up the first (and only) block:
    head->size = pool_size - sizeof(BlockHeader);  // Total size minus header size
    head->is_free = true;                          // Initially, everything is free
    head->next = nullptr;                          // No next block yet
    
    std::cout << "📦 Initialized with one large free block:\n";
    std::cout << "   Header size: " << sizeof(BlockHeader) << " bytes\n";
    std::cout << "   User data size: " << head->size << " bytes\n";
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

// Step 2: Function to visualize all blocks in our memory pool
void MemoryPool::printBlocks() {
    std::cout << "\n🔍 Memory Block Analysis:\n";
    std::cout << "----------------------------------------\n";
    
    BlockHeader* current = head;  // Start from the first block
    int block_number = 0;
    
    // Walk through the linked list of blocks
    while (current != nullptr) {
        std::cout << "Block " << block_number << ":\n";
        std::cout << "  Address: " << current << "\n";
        std::cout << "  Size: " << current->size << " bytes\n";
        std::cout << "  Status: " << (current->is_free ? "FREE" : "USED") << "\n";
        std::cout << "  Next: " << current->next << "\n\n";
        
        // Move to next block
        current = current->next;
        block_number++;
    }
    
    std::cout << "----------------------------------------\n";
}
