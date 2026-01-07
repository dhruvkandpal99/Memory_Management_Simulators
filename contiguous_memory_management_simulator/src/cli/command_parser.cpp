#include "cli/command_parser.h"

#include <iostream>
#include <sstream>

#include "allocator/allocator.h"

// Forward declarations of allocator factory helpers
std::unique_ptr<AllocatorStrategy> createFirstFitAllocator();
std::unique_ptr<AllocatorStrategy> createBestFitAllocator();
std::unique_ptr<AllocatorStrategy> createWorstFitAllocator();

CommandParser::CommandParser(MemoryManager& mm)
    : mm_(mm) {}

bool CommandParser::execute(const std::string& command) {
    std::istringstream iss(command);
    std::string token;

    iss >> token;
    if (token.empty()) {
        return true;
    }

    if (token == "help") {
        std::cout << "Available commands:\n";
        std::cout << "  init memory <size>          Initialize memory\n";
        std::cout << "  set allocator first_fit     Use First-Fit allocator\n";
        std::cout << "  set allocator best_fit      Use Best-Fit allocator\n";
        std::cout << "  set allocator worst_fit     Use Worst-Fit allocator\n";
        std::cout << "  malloc <size>               Allocate memory\n";
        std::cout << "  free <block_id>             Free allocated block\n";
        std::cout << "  dump                        Show block IDs and memory layout\n";
        std::cout << "  help                        Show this help\n";
        std::cout << "  exit | quit                 Exit simulator\n";
        std::cout << "  compact                     Compact memory blocks\n";
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return true;
    }

    if (token == "exit" || token == "quit") {
        return false;
    }

    if (token == "init") {
        std::string mem;
        size_t size;
        iss >> mem >> size; // expect: init memory <size>
        if (mem == "memory") {
            mm_.init(size);
        } else {
            std::cout << "Usage: init memory <size>\n";
        }
        return true;
    }

    if (token == "set") {
        std::string what, which;
        iss >> what >> which; // expect: set allocator <type>
        if (what == "allocator") {
            if (which == "first_fit") {
                mm_.setAllocator(createFirstFitAllocator());
            } else if (which == "best_fit") {
                mm_.setAllocator(createBestFitAllocator());
            } else if (which == "worst_fit") {
                mm_.setAllocator(createWorstFitAllocator());
            } else {
                std::cout << "Unknown allocator type\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }
        }
        return true;
    }

    if (token == "malloc") {
        size_t size;
        iss >> size;
        int id = mm_.malloc(size);
        if (id == -1) {
            std::cout << "Allocation failed\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        } else {
            std::cout << "Allocated block id=" << id << "\n";
        }
        return true;
    }

    if (token == "free") {
        int id;
        iss >> id;
        if (!mm_.free(id)) {
            std::cout << "Invalid block id\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
        return true;
    }

    if (token == "dump") {
        std::cout << "Block Map:\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "ID\tStart\t\tSize\t\tStatus\n";
        std::cout << "------------------------------------------------\n";

        for (const auto& b : mm_.getBlocks()) {
            if (b.free) {
                std::cout << "-\t0x" << std::hex << b.start
                          << std::dec << "\t\t" << b.size
                          << "\t\tFREE\n";
            } else {
                std::cout << b.block_id << "\t0x"
                          << std::hex << b.start
                          << std::dec << "\t\t" << b.size
                          << "\t\tUSED\n";
            }
        }

        std::cout << "------------------------------------------------\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return true;
    }

    if (token == "compact") {
        mm_.compact();
        std::cout << "Memory compacted successfully\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return true;
    }

    std::cout << "Unknown command\n";
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    return true;
}