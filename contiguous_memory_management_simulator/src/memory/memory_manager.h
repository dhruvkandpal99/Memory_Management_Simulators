#pragma once

#include <cstddef>
#include <list>
#include <memory>

#include "allocator/block.h"
#include "memory/stats.h"

// Forward declarations
class AllocatorStrategy;
struct Stats;

// Manages the fixed-size physical memory and delegates
// block selection to an allocation strategy.
class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager(); 

    // Initialize the simulator with a fixed amount of memory
    void init(size_t total_memory);

    // Set allocation strategy (First Fit / Best Fit / Worst Fit)
    void setAllocator(std::unique_ptr<AllocatorStrategy> strategy);

    // Allocate a block of given size (in bytes)
    // Returns allocated block_id on success, -1 on failure
    int malloc(size_t size);

    // Free a previously allocated block by block_id
    // Returns true on success, false if block_id invalid
    bool free(int block_id);

    // Part of Phase-2: // Compact memory by shifting allocated blocks together to eliminate external fragmentation
    void compact();

    // Read-only accessors (used by UI / stats)
    const std::list<Block>& getBlocks() const;
    const Stats& getStats() const;

    size_t getTotalMemory() const;

private:
    // Internal helpers
    void splitBlock(std::list<Block>::iterator block_it, size_t size);
    void coalesce(std::list<Block>::iterator block_it);

private:
    size_t total_memory_;
    int next_block_id_;

    // Memory represented as a list of contiguous blocks
    std::list<Block> blocks_;
    Stats stats_;

    // Current allocation strategy
    std::unique_ptr<AllocatorStrategy> allocator_;
};