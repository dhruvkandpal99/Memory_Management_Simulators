#include "memory/stats.h"

#include <algorithm>

Stats Stats::compute(const std::list<Block>& blocks, size_t total_mem) {
    Stats s{};
    s.total_memory = total_mem;
    s.used_memory = 0;
    s.free_memory = 0;
    s.largest_free_block = 0;

    for (const auto& b : blocks) {
        if (b.free) {
            s.free_memory += b.size;
            s.largest_free_block = std::max(s.largest_free_block, b.size);
        } else {
            s.used_memory += b.size;
        }
    }

    if (s.free_memory == 0) {
        s.external_fragmentation = 0.0;
    } else {
        s.external_fragmentation = 1.0 - (double)s.largest_free_block / (double)s.free_memory;
    }

    return s;
}

void Stats::update(const std::list<Block>& blocks, size_t total) {
    total_memory = total;
    used_memory = 0;
    free_memory = 0;
    largest_free_block = 0;

    for (const auto& b : blocks) {
        if (b.free) {
            free_memory += b.size;
            largest_free_block = std::max(largest_free_block, b.size);
        } else {
            used_memory += b.size;
        }
    }

    if (free_memory == 0 || largest_free_block == free_memory) {
        external_fragmentation = 0.0;
    } else {
        external_fragmentation =
            1.0 - (double)largest_free_block / (double)free_memory;
    }
}