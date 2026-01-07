#ifndef CACHE_SET_H
#define CACHE_SET_H

#include <deque>
#include "cache_line.h"

class CacheSet {
private:
    // A deque acts as a queue for FIFO.
    std::deque<CacheLine> ways; 
    int associativity;

public:
    // Constructor to set how many blocks fit in this set
    CacheSet(int associativity);

    // Checks if tag exists. Returns true on Hit.
    bool contains(unsigned long tag);

    // Adds a tag. If full, removes oldest (FIFO) and returns the evicted tag.
    // Returns -1 (or similar indicator) if nothing was evicted.
    unsigned long insert(unsigned long tag);
};

#endif // CACHE_SET_H