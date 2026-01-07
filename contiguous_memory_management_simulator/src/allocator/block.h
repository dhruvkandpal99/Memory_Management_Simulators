#pragma once

#include <cstddef>

// Represents a contiguous partition of the fixed-size physical memory.
// Blocks form a doubly-linked list that always covers the entire memory.
struct Block {
    size_t start;     // Offset from base address (0 .. TOTAL_MEMORY-1)
    size_t size;      // Size of this block in bytes
    bool free;        // true = free, false = allocated
    int block_id;     // Valid only if allocated; -1 if free

    Block* prev;      // Previous block in memory order
    Block* next;      // Next block in memory order

    Block(size_t start_, size_t size_, bool free_ = true, int id_ = -1)
        : start(start_), size(size_), free(free_), block_id(id_), prev(nullptr), next(nullptr) {}
};