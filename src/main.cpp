// src/main.cpp
// Step 2: Testing Block Metadata
#include <iostream>
#include "allocator.hpp"

int main() {
    std::cout << "=== Step 2: Memory Pool with Block Metadata ===\n\n";

    // Test 1: Create a memory pool and examine its block structure
    std::cout << "📝 Test 1: Creating 1KB memory pool and examining blocks...\n";
    MemoryPool pool(1024);
    
    std::cout << "\nPool Information:\n";
    std::cout << "  Pool Start: " << pool.getPoolStart() << "\n";
    std::cout << "  Pool Size: " << pool.getPoolSize() << " bytes\n";
    
    // NEW: Show the block structure
    pool.printBlocks();

    // Test 2: Show memory layout calculation
    std::cout << "📝 Test 2: Understanding memory layout...\n";
    std::cout << "  Total pool size: 1024 bytes\n";
    // We can't directly access BlockHeader size from here since it's private
    // But we can see it in the output from the constructor
    
    std::cout << "\n🎉 Step 2 Complete!\n";
    std::cout << "✅ We can now track memory blocks with metadata\n";
    std::cout << "✅ Each block knows its size and whether it's free\n";
    std::cout << "✅ Blocks are connected in a linked list\n";
    std::cout << "\nNext: Step 3 - Implement basic allocation (my_malloc)\n";

    return 0;
}
