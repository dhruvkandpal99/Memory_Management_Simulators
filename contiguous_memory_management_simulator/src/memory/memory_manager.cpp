#include "memory_manager.h"

#include <algorithm>

#include "allocator/allocator.h"
#include "memory/stats.h"

MemoryManager::MemoryManager()
    : total_memory_(0), next_block_id_(1), allocator_(nullptr) {}

MemoryManager::~MemoryManager() = default;

void MemoryManager::init(size_t total_memory) {
    total_memory_ = total_memory;
    next_block_id_ = 1;
    blocks_.clear();

    // 1. Create the initial block
    blocks_.emplace_back(0, total_memory_, true, -1);
    
    // 2. Setup the internal pointers for this first block
    blocks_.front().prev = nullptr;
    blocks_.front().next = nullptr;

    // 3. IMMEDIATELY update stats so the UI doesn't show garbage
    stats_.update(blocks_, total_memory_);

    stats_.successful_allocations = 0;
    stats_.failed_allocations = 0;
    stats_.update(blocks_, total_memory_);
}

void MemoryManager::setAllocator(std::unique_ptr<AllocatorStrategy> strategy) {
    allocator_ = std::move(strategy);
}

int MemoryManager::malloc(size_t size) {
    if (!allocator_ || size == 0) {
        stats_.failed_allocations++; // Track failure
        return -1;
    }

    auto block_it = allocator_->findBlock(blocks_, size);
    if (block_it == blocks_.end()) {
        stats_.failed_allocations++; // Track failure
        return -1;
    }

    // Success logic
    int id = next_block_id_++;
    splitBlock(block_it, size);
    block_it->free = false;
    block_it->block_id = id;

    stats_.successful_allocations++; // Track success
    stats_.update(blocks_, total_memory_);
    
    return id;
}

bool MemoryManager::free(int block_id) {
    for (auto it = blocks_.begin(); it != blocks_.end(); ++it) {
        if (!it->free && it->block_id == block_id) {
            it->free = true;
            it->block_id = -1;
            coalesce(it);
            stats_.update(blocks_, total_memory_);
            return true;
        }
    }
    return false; // Invalid block_id
}

const std::list<Block>& MemoryManager::getBlocks() const {
    return blocks_;
}

const Stats& MemoryManager::getStats() const {
    return stats_;
}

size_t MemoryManager::getTotalMemory() const {
    return total_memory_;
}

void MemoryManager::splitBlock(std::list<Block>::iterator block_it, size_t size) {
    if (block_it->size <= size) return;

    size_t remaining_size = block_it->size - size;
    size_t new_start = block_it->start + size;

    block_it->size = size;

    auto next_it = std::next(block_it);
    // Insert new block
    auto new_it = blocks_.insert(next_it, Block(new_start, remaining_size, true, -1));

    // Fix pointers for the split
    new_it->prev = &(*block_it);
    new_it->next = block_it->next;
    if (new_it->next) new_it->next->prev = &(*new_it);
    block_it->next = &(*new_it);
}

void MemoryManager::coalesce(std::list<Block>::iterator block_it) {
    // Merge with previous block if free
    if (block_it != blocks_.begin()) {
        auto prev_it = std::prev(block_it);
        if (prev_it->free) {
            prev_it->size += block_it->size;
            blocks_.erase(block_it);
            block_it = prev_it;
        }
    }

    // Merge with next block if free
    auto next_it = std::next(block_it);
    if (next_it != blocks_.end() && next_it->free) {
        block_it->size += next_it->size;
        blocks_.erase(next_it);
    }
}

void MemoryManager::compact() {
    // 1. Create a temporary list to hold only the allocated blocks
    std::list<Block> allocated_blocks;
    size_t current_offset = 0;

    for (auto& block : blocks_) {
        if (!block.free) {
            // Update the start position for compaction
            block.start = current_offset;
            current_offset += block.size;
            
            // Move the actual block object to the new list
            allocated_blocks.push_back(std::move(block));
        }
    }

    // 2. Clear the main list and move the allocated blocks back in
    blocks_ = std::move(allocated_blocks);

    // 3. Add the single large free block at the end if space remains
    if (current_offset < total_memory_) {
        blocks_.emplace_back(
            current_offset, 
            total_memory_ - current_offset, 
            true, 
            -1
        );
    }

    // 4. FIX THE POINTERS: std::list nodes have stable addresses, 
    // but the internal Block* prev/next must point to the new neighbors.
    Block* last_block = nullptr;
    for (auto& b : blocks_) {
        b.prev = last_block;
        if (last_block) {
            last_block->next = &b;
        }
        last_block = &b;
    }
    if (last_block) {
        last_block->next = nullptr;
    }

    // 5. Update statistics
    stats_.update(blocks_, total_memory_);
}