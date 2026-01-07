CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

# Source files
SRC = src/main.cpp \
      src/cache/cache.cpp \
      src/cache/cache_set.cpp \
      src/hierarchy/cache_hierarchy.cpp \
      src/stats/cache_stats.cpp 


# Output binary
TARGET = cache_sim

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)