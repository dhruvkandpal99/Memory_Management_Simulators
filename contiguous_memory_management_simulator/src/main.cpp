#include <iostream>
#include <string>

#include "memory/memory_manager.h"
#include "ui/dashboard.h"
#include "cli/command_parser.h"

int main() {
    MemoryManager memoryManager;
    Dashboard dashboard;
    CommandParser parser(memoryManager);

    bool running = true;
    std::string command;

    while (running) {
        // Clear terminal (works on macOS/Linux)
        system("clear");

        // Render dashboard
        dashboard.render(memoryManager);

        // Read command
        std::cout << "\n> ";
        std::getline(std::cin, command);

        running = parser.execute(command);
    }

    std::cout << "Exiting memory simulator.\n";
    return 0;
}