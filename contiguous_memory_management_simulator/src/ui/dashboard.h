#pragma once

#include "memory/memory_manager.h"

// Renders an always-on CLI dashboard for memory visualization
class Dashboard {
public:
    void render(const MemoryManager& mm) const;
};