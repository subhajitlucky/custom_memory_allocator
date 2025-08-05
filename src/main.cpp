// src/main.cpp
#include <iostream>
#include "allocator.hpp"

int main() {
    std::cout << "=== Step 1: Project Setup ===\n\n";

    std::cout << "Test 1: Creating 1KB memory pool...\n";
    MemoryPool small_pool(1024);
    std::cout << "Pool Start: " << small_pool.getPoolStart() << "\n";
    std::cout << "Pool Size: " << small_pool.getPoolSize() << " bytes\n\n";

    std::cout << "Test 2: Creating 1MB memory pool...\n";
    MemoryPool large_pool(1024 * 1024);
    std::cout << "Pool Start: " << large_pool.getPoolStart() << "\n";
    std::cout << "Pool Size: " << large_pool.getPoolSize() << " bytes\n\n";

    if (small_pool.getPoolStart() != large_pool.getPoolStart()) {
        std::cout << "SUCCESS: Each pool has unique memory space!\n";
    }

    std::cout << "\nStep 1 Complete!\n";
    return 0;
}
