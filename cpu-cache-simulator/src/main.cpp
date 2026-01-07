#include <iostream>
#include <vector>
#include "hierarchy/cache_hierarchy.h"

int main(int argc, char* argv[]) {
    std::cout << "Starting Multi-Level Cache Simulation...\n";

    // 1. Create the Hierarchy (L1 + L2)
    CacheHierarchy memorySystem;

    // 2. Define a memory trace (Access Patterns).
    std::vector<unsigned long> memoryTrace = {
        // --- PHASE 1: FILL THE L1 ---
        0x1000, // 1. Cold Miss.   L1: [A]       | L2: [A]
        0x2000, // 2. Cold Miss.   L1: [A, B]    | L2: [A, B]
        
        // --- PHASE 2: FORCE EVICTION  ---
        0x3000, // 3. Cold Miss.   
                //    L1 is full! Evicts A (FIFO). 
                //    L1: [B, C]   | L2: [A, B, C]

        // --- PHASE 3: THE L2 RESCUE ---
        0x1000, // 4. L1 Miss (A is gone). 
                //    L2 Check: HIT! (A is still in L2).
                //    Action: Bring A back to L1. Evicts B.
                //    L1: [C, A]   | L2: [A, B, C]

        0x2000, // 5. L1 Miss (B was just evicted!).
                //    L2 Check: HIT!
                //    Action: Bring B back to L1. Evicts C.
                //    L1: [A, B]   | L2: [A, B, C]

        // --- PHASE 4: IMMEDIATE HIT ---
        0x2000, // 6. L1 HIT (B is right there).
                //    L1: [A, B] (No change)
                
        // --- PHASE 5: NEW BLOCK ---
        0x4000  // 7. Cold Miss. 
                //    L1 Evicts A. 
                //    L1: [B, D]   | L2: [A, B, C, D]
    };

    // 3. Run the Simulation
    int opCount = 0;
    for (unsigned long address : memoryTrace) {
        memorySystem.access(address);
        opCount++;
    }

    std::cout << "Processed " << opCount << " memory accesses.\n\n";

    // 4. Print Report
    memorySystem.printStats();

    return 0;
}