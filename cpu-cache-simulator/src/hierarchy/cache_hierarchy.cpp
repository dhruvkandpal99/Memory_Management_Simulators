#include <iostream>
#include <iomanip>
#include "cache_hierarchy.h"

CacheHierarchy::CacheHierarchy() {
    // TINY L1: Can only hold 2 items total!
    // Size = 128 bytes, Block = 64, Assoc = 2
    l1 = std::make_unique<Cache>("L1", 128, 64, 2);

    // HUGE L2: Holds everything we throw at it
    // Size = 4096 bytes (4KB), Block = 64, Assoc = 4
    l2 = std::make_unique<Cache>("L2", 4096, 64, 4);
}

void CacheHierarchy::access(unsigned long address) {
    // 1. Attempt L1 Access
    // ------------------------------------------------
    bool l1Hit = l1->access(address);
    total_cycles += L1_LATENCY;

    if (l1Hit) {
        return; // Done! Data found in L1.
    }

    // 2. L1 Miss -> Attempt L2 Access
    // ------------------------------------------------
    bool l2Hit = l2->access(address);
    total_cycles += L2_LATENCY; // Add L2 penalty

    if (l2Hit) {
        // L2 Hit: We found it in L2.
        // Action: Bring data "up" to L1 so it's faster next time.
        l1->insert(address);
        return;
    }

    // 3. L2 Miss -> Fetch from Main Memory
    // ------------------------------------------------
    total_cycles += RAM_LATENCY; // Add huge RAM penalty

    // Action: Bring data from RAM -> L2 -> L1
    l2->insert(address);
    l1->insert(address);
}

void CacheHierarchy::printStats() {
    std::cout << "========================================\n";
    std::cout << "          SIMULATION RESULTS            \n";
    std::cout << "========================================\n";
    
    // Helper lambda for clean printing
    auto printLevel = [](Cache& c) {
        std::cout << "Cache Stats (" << c.getName() << "):\n";
        std::cout << "  Hits:   " << c.stats.hits << "\n";
        std::cout << "  Misses: " << c.stats.misses << "\n";
        std::cout << "  Rate:   " << std::fixed << std::setprecision(2) 
                  << (c.stats.getHitRate() * 100.0) << "%\n\n";
    };

    // Now actually USE the lambda
    printLevel(*l1);
    printLevel(*l2);

    std::cout << "Performance:\n";
    std::cout << "  Total Cycles: " << total_cycles << "\n";
}