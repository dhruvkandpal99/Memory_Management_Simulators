#include <iostream>
#include "cache.h"

Cache::Cache(std::string name, size_t size, size_t blockSize, int associativity)
    : name(name), block_size(blockSize)
{
    // 1. Calculate Number of Sets
    // NumSets = CacheSize / (BlockSize * Associativity)
    num_sets = size / (block_size * associativity);

    // 2. Initialize the Sets
    for (int i = 0; i < num_sets; ++i) {
        sets.emplace_back(associativity); // Create CacheSet objects
    }

    // 3. Calculate Bit Widths (Log2)
    // Example: Block size 64 bytes -> log2(64) = 6 bits for offset
    block_offset_bits = (int)std::log2(block_size);
    index_bits = (int)std::log2(num_sets);
}

void Cache::getIndexAndTag(unsigned long address, int& index, unsigned long& tag) {
    // Bitwise magic to extract bits
    
    // 1. Discard the Offset (shift right)
    unsigned long shifted = address >> block_offset_bits;

    // 2. Extract Index (Mask the lower bits)
    // Example: if index_bits is 3, mask is 111 (binary) which is 7
    int index_mask = (1 << index_bits) - 1;
    index = shifted & index_mask;

    // 3. Extract Tag (Shift remaining bits)
    tag = shifted >> index_bits;
}

bool Cache::access(unsigned long address) {
    int index;
    unsigned long tag;
    getIndexAndTag(address, index, tag);

    bool hit = sets[index].contains(tag);

    if (hit) {
        stats.hits++;
        // Log Hit
        std::cout << "[" << name << "] HIT  Addr: " << std::hex << address << std::dec << "\n";
    } else {
        stats.misses++;
        // Log Miss
        std::cout << "[" << name << "] MISS Addr: " << std::hex << address << std::dec << "\n";
    }

    return hit;
}

void Cache::insert(unsigned long address) {
    int index;
    unsigned long tag;
    getIndexAndTag(address, index, tag);

    sets[index].insert(tag);
}