#ifndef CACHE_STATS_H
#define CACHE_STATS_H

struct CacheStats {
    long long hits = 0;
    long long misses = 0;
    
    // Declaration only
    double getHitRate() const;
};

#endif // CACHE_STATS_H