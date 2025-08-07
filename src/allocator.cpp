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

// Step 3: Our custom malloc implementation
void* MemoryPool::my_malloc(size_t size) {
    std::cout << "🔍 my_malloc(" << size << ") called\n";
    
    // Step 1: Search for a suitable free block
    BlockHeader* current = head;  // Start from the first block
    
    while (current != nullptr) {
        std::cout << "  Checking block at " << current 
                  << " (size=" << current->size 
                  << ", free=" << current->is_free << ")\n";
        
        // Check if this block is free AND big enough
        if (current->is_free && current->size >= size) {
            std::cout << "  ✅ Found suitable block!\n";
            
            // Step 2: Should we split this block?
            // Only split if remaining space is worth keeping
            // (must be big enough for another BlockHeader + some data)
            if (current->size >= size + sizeof(BlockHeader) + 1) {
                std::cout << "  ✂️ Splitting block...\n";
                
                // Calculate where the new block will start
                // current block + header + user data size
                char* new_block_address = reinterpret_cast<char*>(current) 
                                        + sizeof(BlockHeader) + size;
                
                // Create the new block header
                BlockHeader* new_block = reinterpret_cast<BlockHeader*>(new_block_address);
                new_block->size = current->size - size - sizeof(BlockHeader);
                new_block->is_free = true;
                new_block->next = current->next;  // Point to what current was pointing to
                
                // Update current block
                current->size = size;  // Shrink current block to exact size needed
                current->next = new_block;  // Point to our new block
                
                std::cout << "    Original block now: " << size << " bytes\n";
                std::cout << "    New block: " << new_block->size << " bytes\n";
            }
            
            // Step 3: Mark block as used
            current->is_free = false;
            
            // Step 4: Return pointer to usable memory (after the header)
            void* user_ptr = reinterpret_cast<char*>(current) + sizeof(BlockHeader);
            
            std::cout << "  📦 Allocated " << size << " bytes at " << user_ptr << "\n";
            return user_ptr;
        }
        
        // Move to next block
        current = current->next;
    }
    
    // No suitable block found
    std::cout << "  ❌ No suitable block found for " << size << " bytes\n";
    return nullptr;
}

// Step 4: Our custom free implementation
void MemoryPool::my_free(void* ptr) {
    std::cout << "🔍 my_free(" << ptr << ") called\n";
    
    // Step 1: Handle null pointer
    if (!ptr) {
        std::cout << "  ⚠️ Warning: Cannot free null pointer\n";
        return;
    }
    
    // Step 2: Calculate BlockHeader address from user pointer
    // User pointer = BlockHeader + sizeof(BlockHeader)
    // So: BlockHeader = User pointer - sizeof(BlockHeader)
    BlockHeader* block_to_free = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<char*>(ptr) - sizeof(BlockHeader)
    );
    
    std::cout << "  📍 Block to free at: " << block_to_free << "\n";
    
    // Step 3: Basic validation - check if this looks like a valid block
    // (In a real allocator, we'd do more thorough validation)
    if (block_to_free < memory_start || 
        reinterpret_cast<char*>(block_to_free) >= 
        reinterpret_cast<char*>(memory_start) + pool_size) {
        std::cout << "  ❌ Error: Pointer outside memory pool bounds\n";
        return;
    }
    
    // Step 4: Check if block is already free (double-free detection)
    if (block_to_free->is_free) {
        std::cout << "  ⚠️ Warning: Block is already free! (double-free detected)\n";
        return;
    }
    
    // Step 5: Mark block as free
    block_to_free->is_free = true;
    std::cout << "  ✅ Marked block as free (size: " << block_to_free->size << " bytes)\n";
    
    // Step 6: Coalescing - merge with adjacent free blocks
    std::cout << "  🔗 Looking for adjacent free blocks to merge...\n";
    
    // Walk through all blocks to find and merge adjacent free blocks
    BlockHeader* current = head;
    while (current && current->next) {
        // If current block and next block are both free, merge them
        if (current->is_free && current->next->is_free) {
            std::cout << "    🔄 Merging block at " << current 
                      << " (size:" << current->size 
                      << ") with next block at " << current->next 
                      << " (size:" << current->next->size << ")\n";
                      
            // Merge: current block absorbs the next block
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next;  // Skip the merged block
            
            std::cout << "    ✅ Merged into single block of size: " << current->size << " bytes\n";
            
            // Don't advance current - check again in case there are more adjacent free blocks
        } else {
            current = current->next;
        }
    }
    
    std::cout << "  🎉 Free operation completed!\n";
}
