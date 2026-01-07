#include "cache_set.h"

CacheSet::CacheSet(int assoc) : associativity(assoc) {}

bool CacheSet::contains(unsigned long tag) {
    // Iterate over the deque to find the tag
    for (const auto& line : ways) {
        if (line.valid && line.tag == tag) {
            return true; // HIT
        }
    }
    return false; // MISS
}

unsigned long CacheSet::insert(unsigned long tag) {
    unsigned long evictedTag = 0;
    bool evictionOccurred = false;

    // 1. Check if we need to evict (is the set full?)
    if (ways.size() >= associativity) {
        
        evictedTag = ways.front().tag;
        ways.pop_front();
        evictionOccurred = true;
    }

    // 2. Insert the new line at the BACK
    CacheLine newLine;
    newLine.tag = tag;
    newLine.valid = true;
    ways.push_back(newLine);

    // Return the evicted tag if one was removed, otherwise a safety value
    return evictionOccurred ? evictedTag : -1; 
}