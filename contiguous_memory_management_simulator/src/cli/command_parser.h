#pragma once

#include <string>

#include "memory/memory_manager.h"

// Parses and executes user commands for the simulator
class CommandParser {
public:
    explicit CommandParser(MemoryManager& mm);

    // Execute a single command line
    // Returns false if the program should exit
    bool execute(const std::string& command);

private:
    MemoryManager& mm_;
};