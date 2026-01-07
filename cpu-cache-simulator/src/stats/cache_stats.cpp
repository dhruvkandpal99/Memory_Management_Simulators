#include "cache_stats.h"

double CacheStats::getHitRate() const {
    long long total = hits + misses;
    if (total == 0) {
        return 0.0;
    }
    return (double)hits / total;
}