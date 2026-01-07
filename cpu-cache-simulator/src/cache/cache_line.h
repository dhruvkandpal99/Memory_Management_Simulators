#ifndef CACHE_LINE_H
#define CACHE_LINE_H

struct CacheLine {
    unsigned long tag;
    bool valid;

    CacheLine() : tag(0), valid(false) {}
};

#endif // CACHE_LINE_H