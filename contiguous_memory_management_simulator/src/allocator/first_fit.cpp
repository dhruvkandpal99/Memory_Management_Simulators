#include "allocator/allocator.h"

// First Fit allocation strategy
class FirstFitAllocator : public AllocatorStrategy {
public:
    std::list<Block>::iterator findBlock(std::list<Block>& blocks, size_t size) override {
        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            if (it->free && it->size >= size) {
                return it;
            }
        }
        return blocks.end();
    }
};

// Factory function (optional helper)
std::unique_ptr<AllocatorStrategy> createFirstFitAllocator() {
    return std::make_unique<FirstFitAllocator>();
}