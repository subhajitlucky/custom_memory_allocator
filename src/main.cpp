#include <iostream>
#include "allocator.hpp"

int main() {
    std::cout << "Custom Memory Allocator - Starting Project" << std::endl;

    MemoryPool pool(1024 * 1024);
    std::cout << "Pool Start Address: " << pool.getPoolStart() << std::endl;
    std::cout << "Pool Size: " << pool.getPoolSize() << " bytes" << std::endl;

    pool.printBlocks(); // NEW: show block structure

    std::cout << "\nAllocating 100 bytes..." << std::endl;
    void* ptr = pool.my_malloc(100);
    std::cout << "Allocated at: " << ptr << std::endl;
    pool.printBlocks(); // show blocks after allocation

    std::cout << "\nFreeing the allocated block..." << std::endl;
    pool.deallocate(ptr);
    std::cout << "After deallocation:" << std::endl;
    pool.printBlocks(); // show blocks after deallocation

    return 0;
}
