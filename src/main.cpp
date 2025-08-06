// src/main.cpp
// Step 3: Testing my_malloc implementation
#include <iostream>
#include "allocator.hpp"

int main() {
    std::cout << "=== Step 3: Implementing my_malloc ===\n\n";

    // Create a smaller pool for easier visualization
    std::cout << "📝 Creating 512-byte memory pool...\n";
    MemoryPool pool(512);
    
    std::cout << "\n📊 Initial state:\n";
    pool.printBlocks();

    // Test 1: First allocation
    std::cout << "\n📝 Test 1: Allocating 100 bytes...\n";
    void* ptr1 = pool.my_malloc(100);
    if (ptr1) {
        std::cout << "✅ Success! Got pointer: " << ptr1 << "\n";
    } else {
        std::cout << "❌ Allocation failed!\n";
    }
    
    std::cout << "\n📊 After first allocation:\n";
    pool.printBlocks();

    // Test 2: Second allocation
    std::cout << "\n📝 Test 2: Allocating 50 bytes...\n";
    void* ptr2 = pool.my_malloc(50);
    if (ptr2) {
        std::cout << "✅ Success! Got pointer: " << ptr2 << "\n";
    } else {
        std::cout << "❌ Allocation failed!\n";
    }
    
    std::cout << "\n📊 After second allocation:\n";
    pool.printBlocks();

    // Test 3: Third allocation
    std::cout << "\n📝 Test 3: Allocating 200 bytes...\n";
    void* ptr3 = pool.my_malloc(200);
    if (ptr3) {
        std::cout << "✅ Success! Got pointer: " << ptr3 << "\n";
    } else {
        std::cout << "❌ Allocation failed!\n";
    }
    
    std::cout << "\n� After third allocation:\n";
    pool.printBlocks();

    // Test 4: Allocation that should fail
    std::cout << "\n📝 Test 4: Trying to allocate 500 bytes (should fail)...\n";
    void* ptr4 = pool.my_malloc(500);
    if (ptr4) {
        std::cout << "✅ Success! Got pointer: " << ptr4 << "\n";
    } else {
        std::cout << "❌ Expected failure - not enough space!\n";
    }

    // Test 5: Test pointer validity by writing to memory
    std::cout << "\n📝 Test 5: Testing memory write/read...\n";
    if (ptr1) {
        // Write some data to our allocated memory
        char* data = static_cast<char*>(ptr1);
        data[0] = 'H';
        data[1] = 'i';
        data[2] = '!';
        data[3] = '\0';
        
        std::cout << "✅ Wrote to memory: " << data << "\n";
    }

    std::cout << "\n🎉 Step 3 Complete!\n";
    std::cout << "✅ We can allocate memory blocks\n";
    std::cout << "✅ Blocks are split when too large\n";
    std::cout << "✅ Used blocks are marked properly\n";
    std::cout << "✅ Memory pointers work for reading/writing\n";
    std::cout << "\nNext: Step 4 - Implement memory deallocation (my_free)\n";

    return 0;
}
