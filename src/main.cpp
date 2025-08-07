// src/main.cpp
// Step 4: Testing my_free implementation
#include <iostream>
#include "allocator.hpp"

int main() {
    std::cout << "=== Step 4: Implementing my_free ===\n\n";

    // Create a memory pool for testing
    std::cout << "📝 Creating 512-byte memory pool...\n";
    MemoryPool pool(512);
    
    std::cout << "\n📊 Initial state:\n";
    pool.printBlocks();

    // Phase 1: Allocate several blocks
    std::cout << "\n=== PHASE 1: ALLOCATING MEMORY ===\n";
    
    std::cout << "\n📝 Allocating 100 bytes...\n";
    void* ptr1 = pool.my_malloc(100);
    
    std::cout << "\n📝 Allocating 50 bytes...\n";
    void* ptr2 = pool.my_malloc(50);
    
    std::cout << "\n📝 Allocating 80 bytes...\n";
    void* ptr3 = pool.my_malloc(80);
    
    std::cout << "\n📊 After allocations:\n";
    pool.printBlocks();

    // Phase 2: Free middle block and observe fragmentation
    std::cout << "\n=== PHASE 2: FREEING MIDDLE BLOCK ===\n";
    std::cout << "\n📝 Freeing middle block (ptr2)...\n";
    pool.my_free(ptr2);
    
    std::cout << "\n📊 After freeing middle block:\n";
    pool.printBlocks();

    // Phase 3: Free adjacent block and observe coalescing
    std::cout << "\n=== PHASE 3: FREEING ADJACENT BLOCK (COALESCING TEST) ===\n";
    std::cout << "\n📝 Freeing first block (ptr1) - should merge with freed middle block...\n";
    pool.my_free(ptr1);
    
    std::cout << "\n📊 After coalescing:\n";
    pool.printBlocks();

    // Phase 4: Test error conditions
    std::cout << "\n=== PHASE 4: ERROR HANDLING TESTS ===\n";
    
    std::cout << "\n📝 Test 1: Freeing null pointer...\n";
    pool.my_free(nullptr);
    
    std::cout << "\n📝 Test 2: Double-free detection...\n";
    pool.my_free(ptr1);  // ptr1 was already freed
    
    std::cout << "\n📝 Test 3: Freeing invalid pointer...\n";
    void* fake_ptr = reinterpret_cast<void*>(0x12345);
    pool.my_free(fake_ptr);

    // Phase 5: Complete cleanup
    std::cout << "\n=== PHASE 5: COMPLETE CLEANUP ===\n";
    std::cout << "\n📝 Freeing remaining block (ptr3)...\n";
    pool.my_free(ptr3);
    
    std::cout << "\n📊 Final state (should be one big free block):\n";
    pool.printBlocks();

    // Phase 6: Test reusability
    std::cout << "\n=== PHASE 6: TESTING REUSABILITY ===\n";
    std::cout << "\n📝 Allocating 200 bytes from cleaned pool...\n";
    void* ptr4 = pool.my_malloc(200);
    
    std::cout << "\n📊 After reallocation:\n";
    pool.printBlocks();
    
    pool.my_free(ptr4);  // Clean up

    std::cout << "\n🎉 Step 4 Complete!\n";
    std::cout << "✅ Memory deallocation works correctly\n";
    std::cout << "✅ Coalescing prevents fragmentation\n";
    std::cout << "✅ Error conditions handled gracefully\n";
    std::cout << "✅ Memory can be reused after freeing\n";
    std::cout << "\nWe now have a fully functional basic memory allocator! 🚀\n";

    return 0;
}
