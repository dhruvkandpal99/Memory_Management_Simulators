#pragma once

#include <list>

#include "allocator/block.h"

// Strategy interface for memory allocation policies
class AllocatorStrategy {
public:
    virtual ~AllocatorStrategy() = default;

    // Given the list of memory blocks, find a suitable free block
    // that can satisfy an allocation of 'size' bytes.
    // Returns iterator to the chosen block, or blocks.end() if none found.
    virtual std::list<Block>::iterator findBlock(std::list<Block>& blocks,
                                                 size_t size) = 0;
};