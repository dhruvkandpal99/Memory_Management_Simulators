#ifndef CACHE_HIERARCHY_H
#define CACHE_HIERARCHY_H

#include <memory>
#include "../cache/cache.h"

class CacheHierarchy {
private:
    std::unique_ptr<Cache> l1;
    std::unique_ptr<Cache> l2;
    
    // Simulated Performance Metrics
    long long total_cycles = 0;

    // Hardcoded Latencies (you could make these configurable)
    const int L1_LATENCY = 1;
    const int L2_LATENCY = 10;
    const int RAM_LATENCY = 100;

public:
    CacheHierarchy(); // We can hardcode sizes here or pass them in
    
    // The main entry point for the CPU
    void access(unsigned long address);
    
    void printStats();
};

#endif // CACHE_HIERARCHY_H