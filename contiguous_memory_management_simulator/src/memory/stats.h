#pragma once

#include <list>
#include <cstddef>

#include "allocator/block.h"

// Aggregated statistics about memory usage
struct Stats {
    size_t total_memory = 0;
    size_t used_memory = 0;
    size_t free_memory = 0;
    size_t largest_free_block = 0;
    double external_fragmentation = 0.0;

    // Recompute stats based on current memory blocks
    void update(const std::list<Block>& blocks, size_t total);

    static Stats compute(const std::list<Block>& blocks, size_t total_memory);

    size_t successful_allocations = 0;
    size_t failed_allocations = 0;

    double getSuccessRate() const {
        size_t total = successful_allocations + failed_allocations;
        if (total == 0) return 0.0;
        return (static_cast<double>(successful_allocations) / total) * 100.0;
    }
};