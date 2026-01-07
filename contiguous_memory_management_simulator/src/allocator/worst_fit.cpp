#include "allocator/allocator.h"

#include <limits>

// Worst Fit allocation strategy
class WorstFitAllocator : public AllocatorStrategy {
public:
    std::list<Block>::iterator findBlock(std::list<Block>& blocks, size_t size) override {
        auto worst_it = blocks.end();
        size_t worst_size = 0;

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size && it->size > worst_size) {
                worst_size = it->size;
                worst_it = it;
            }
        }
        return worst_it;
    }
};

// Factory function (optional helper)
std::unique_ptr<AllocatorStrategy> createWorstFitAllocator() {
    return std::make_unique<WorstFitAllocator>();
}