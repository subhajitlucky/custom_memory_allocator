# Custom Memory Allocator Roadmap

This document outlines the step-by-step plan to build a robust, cross-platform memory allocator.

---

### ✅ **Phase 1: Core Functionality (Complete)**

-   ✅ **Step 1: Project Setup**: Basic C++ project with `Makefile`.
-   ✅ **Step 2: Memory Pool**: Allocate a large, fixed-size memory pool using `std::malloc`.
-   ✅ **Step 3: Block Metadata**: Implement a `BlockHeader` to track block size, status (free/used), and the next block.
-   ✅ **Step 4: `my_malloc`**: Implement a basic allocation function that finds the first-fit free block and can split it.
-   ✅ **Step 5: `my_free`**: Implement a deallocation function that marks blocks as free and merges with the *next* adjacent free block.

---

### 🚀 **Phase 2: Robustness and Alignment**

-   ❌ **Step 6: Memory Alignment**:
    -   [ ] Modify `my_malloc` to return pointers aligned to a standard boundary (e.g., 8 or 16 bytes).
    -   [ ] Adjust size calculations to account for padding required for alignment.

-   ❌ **Step 7: Bidirectional Coalescing**:
    -   [ ] Update `BlockHeader` to include a `prev` pointer, creating a doubly-linked list.
    -   [ ] Modify `my_free` to check both the `next` and `prev` blocks for merging, to more effectively reduce fragmentation.

-   ❌ **Step 8: Error Handling & Hardening**:
    -   [ ] Add checks to prevent double-freeing a block.
    -   [ ] Implement "canary" values in the block header/footer to detect memory corruption (buffer overflows).
    -   [ ] Add more robust error reporting for out-of-memory conditions.

---

### 🌟 **Phase 3: Feature Completeness**

-   ❌ **Step 9: Implement `my_realloc`**:
    -   [ ] Create a function to resize existing allocations.
    -   [ ] Handle cases for shrinking and growing allocations, including moving data to a new block if necessary.

-   ❌ **Step 10: Implement `my_calloc`**:
    -   [ ] Create a function that allocates memory and initializes it to zero.

-   ❌ **Step 11: Dynamic Pool Growth**:
    -   [ ] When `my_malloc` cannot find a free block, allow the memory pool to request more memory from the OS instead of failing.

---

### ⚡ **Phase 4: Performance and Concurrency**

-   ❌ **Step 12: Free List Optimization**:
    -   [ ] Instead of a single list of all blocks, create a separate linked list exclusively for *free* blocks to speed up `my_malloc`.
    -   [ ] (Advanced) Explore segregated free lists for different size classes.

-   ❌ **Step 13: Thread Safety**:
    -   [ ] Add a mutex lock around critical sections in `my_malloc` and `my_free` to make the allocator safe for use in multi-threaded applications.

---

### 🌐 **Phase 5: Cross-Platform Support**

-   ❌ **Step 14: Windows Compatibility**:
    -   [ ] Replace Linux-specific system calls (if any were added) with their Windows equivalents (e.g., using `VirtualAlloc` instead of `sbrk` or `mmap`).
    -   [ ] Set up a build environment for Windows (e.g., using Visual Studio or MinGW).
    -   [ ] Test and validate the allocator's behavior on the Windows platform.
