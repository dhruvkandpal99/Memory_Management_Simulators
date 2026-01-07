#include "allocator/allocator.h"

#include <limits>

// Best Fit allocation strategy
class BestFitAllocator : public AllocatorStrategy {
public:
    std::list<Block>::iterator findBlock(std::list<Block>& blocks, size_t size) override {
        auto best_it = blocks.end();
        size_t best_size = std::numeric_limits<size_t>::max();

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size && it->size < best_size) {
                best_size = it->size;
                best_it = it;
            }
        }
        return best_it;
    }
};

// Factory function (optional helper)
std::unique_ptr<AllocatorStrategy> createBestFitAllocator() {
    return std::make_unique<BestFitAllocator>();
}