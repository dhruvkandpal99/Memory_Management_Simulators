#include "ui/dashboard.h"
#include "memory/stats.h"

#include <iostream>
#include <iomanip>
#include <cmath>

static const int BAR_WIDTH = 64;

void Dashboard::render(const MemoryManager& mm) const {
    const auto& blocks = mm.getBlocks();
    Stats stats = mm.getStats();

    std::cout << "\033[2J\033[1;1H"; // Optional: Clears screen for a "live" feel
    std::cout << "Memory Management Simulator\n";
    std::cout << "────────────────────────────────────────────────────\n";

    // Standard Memory Stats
    std::cout << std::left << std::setw(12) << "Total" << ": " << stats.total_memory << " bytes\n";
    std::cout << std::left << std::setw(12) << "Used"  << ": " << stats.used_memory << " bytes\n";
    std::cout << std::left << std::setw(12) << "Free"  << ": " << stats.free_memory << " bytes\n";
    
    // Allocation Success/Failure Rate
    size_t total_reqs = stats.successful_allocations + stats.failed_allocations;
    double success_rate = (total_reqs > 0) 
        ? (static_cast<double>(stats.successful_allocations) / total_reqs) * 100.0 
        : 0.0;

    std::cout << std::left << std::setw(12) << "Allocations" << ": " 
              << stats.successful_allocations << " Success / " 
              << stats.failed_allocations << " Fail (" 
              << std::fixed << std::setprecision(1) << success_rate << "%)\n";

    std::cout << std::left << std::setw(12) << "Ext Frag" << ": " 
              << std::fixed << std::setprecision(2)
              << (stats.external_fragmentation * 100.0) << " %\n\n";

    // Memory Map Visualization
    std::cout << "Memory Map:\n[";

    double bytes_per_cell = (double)stats.total_memory / BAR_WIDTH;
    int printed = 0;

    for (const auto& block : blocks) {
        // Calculate how many characters this block occupies
        int cells = (int)std::round(block.size / bytes_per_cell);
        // Ensure even tiny blocks show up if they are allocated
        if (!block.free && cells == 0) cells = 1; 

        const char* symbol = block.free ? "□" : "■";

        for (int i = 0; i < cells && printed < BAR_WIDTH; ++i) {
            std::cout << symbol;
            printed++;
        }
    }

    // Fill remaining bar width
    while (printed < BAR_WIDTH) {
        std::cout << "□";
        printed++;
    }

    std::cout << "]\n";
    std::cout << "Legend: ■ = USED   □ = FREE\n";
    std::cout << "────────────────────────────────────────────────────\n";
    std::cout << "Enter command: " << std::flush;
}