#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <string>
#include <cmath>
#include "cache_set.h"
#include "../stats/cache_stats.h"

class Cache {
private:
    std::string name;             // e.g., "L1", "L2"
    size_t block_size;            // Block size in bytes
    
    int num_sets;
    int index_bits;
    int block_offset_bits;

    std::vector<CacheSet> sets;   // The actual memory

public:
    CacheStats stats;             // Public so we can read it easily later

    Cache(std::string name, size_t size, size_t blockSize, int associativity);

    std::string getName() const { return name; }

    // Main interaction methods
    bool access(unsigned long address);
    void insert(unsigned long address);

private:
    // Helper to strip the offset and separate Tag from Index
    void getIndexAndTag(unsigned long address, int& index, unsigned long& tag);
};

#endif // CACHE_H