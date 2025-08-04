// src/allocator.cpp

#include "allocator.hpp"

MemoryPool::MemoryPool(size_t size) {
    pool_size = size;
    memory_start = std::malloc(pool_size);

    if (!memory_start) {
        std::cerr << "Failed to allocate memory pool\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Memory Pool of " << pool_size << " bytes created at " 
              << memory_start << std::endl;

    // Initialize the first (and only) block as a free block
    head = static_cast<BlockHeader*>(memory_start);
    head->size = pool_size - sizeof(BlockHeader);
    head->is_free = true;
    head->next = nullptr;
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

void MemoryPool::printBlocks() {
    BlockHeader* current = head;
    int index = 0;
    std::cout << "\n[Memory Blocks in Pool]\n";
    while (current) {
        std::cout << "Block " << index++ << ": "
                  << "Address = " << current << ", "
                  << "Size = " << current->size << " bytes, "
                  << "Free = " << (current->is_free ? "Yes" : "No") << ", "
                  << "Next = " << current->next << "\n";
        current = current->next;
    }
    std::cout << "------------------------\n";
}

// Custom malloc implementation (Step 4)
void* MemoryPool::my_malloc(size_t size) {
    BlockHeader* current = head;
    while (current != nullptr) {
        if (current->is_free && current->size >= size) {
            // Split block if it's too big
            if (current->size >= size + sizeof(BlockHeader) + 1) {
                BlockHeader* new_block = reinterpret_cast<BlockHeader*>(
                    reinterpret_cast<char*>(current) + sizeof(BlockHeader) + size);
                new_block->size = current->size - size - sizeof(BlockHeader);
                new_block->is_free = true;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            current->is_free = false;
            // Return pointer to usable memory (after header)
            return reinterpret_cast<void*>(
                reinterpret_cast<char*>(current) + sizeof(BlockHeader));
        }
        current = current->next;
    }
    return nullptr; // No sufficient memory
}


// Step 5: Custom free implementation
void MemoryPool::deallocate(void* ptr) {
    if (!ptr) {
        std::cerr << "Cannot deallocate a null pointer.\n";
        return;
    }

    // Get the block header from the pointer and mark it as free
    BlockHeader* block = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<char*>(ptr) - sizeof(BlockHeader));
    block->is_free = true;

    // Merge adjacent free blocks to reduce fragmentation
    BlockHeader* current = head;
    while (current && current->next) {
        if (current->is_free && current->next->is_free) {
            // Merge current and next blocks
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}