CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRC := \
	src/main.cpp \
	src/memory/memory_manager.cpp \
	src/memory/stats.cpp \
	src/ui/dashboard.cpp \
	src/cli/command_parser.cpp \
	src/allocator/first_fit.cpp \
	src/allocator/best_fit.cpp \
	src/allocator/worst_fit.cpp

INC := -Isrc

TARGET := memsim

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean