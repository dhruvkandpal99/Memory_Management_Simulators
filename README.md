
# Memory Management & Architecture Simulators

This repository contains two C++ simulation projects demonstrating core operating system and computer architecture concepts: a **Multilevel CPU Cache Simulator** and a **Contiguous Memory Management Simulator**.

Detailed design documents and test reports for both projects can be found in the `docs/` directory.

---

## 1. Multilevel CPU Cache Simulator
A simulation of a hierarchical CPU cache (L1 and L2) implementing **FIFO (First-In, First-Out)** replacement policy. It mimics cache hits, misses, and data propagation between cache levels and main memory.

### Features
* **Hierarchy:** L1 Cache (Tiny/Fast) backed by L2 Cache (Large/Slow).
* **Associativity:** Configurable Set-Associative mapping.
* **Metrics:** Reports Hit/Miss counts, Hit Rate, and Total Simulated Cycles.
* **Validation:** Verified against "Thrashing" scenarios and capacity evictions.

### How to Run
Navigate to the project directory, compile using `make`, and run the executable.

```bash
# 1. Enter the directory
cd cpu-cache-simulator

# 2. Compile the source code
make

# 3. Run the simulator
./cache_sim

```

To clean up build artifacts (object files and executables):

```bash
make clean

```

---

## 2. Contiguous Memory Management Simulator

A simulation of an OS memory manager handling process allocation and deallocation. It implements various allocation strategies to manage the heap and combat fragmentation.

### Features

* **Allocation Policies:** First Fit, Best Fit, Worst Fit.
* **Memory Operations:** Allocation (`alloc`), Deallocation (`free`), and Compaction.
* **Visuals:** Dashboard reporting block usage and fragmentation stats.

### How to Run

Navigate to the project directory, compile, and run.

```bash
# 1. Enter the directory
cd contiguous_memory_management_simulator

# 2. Compile the source code
make

# 3. Run the simulator
./memsim

```

To clean up build artifacts:

```bash
make clean

```

---

## Documentation

The `docs/` folder contains detailed reports and test logs for both projects:

* **Cache Simulator:** `docs/Multilevel CPU Cache Simulator Report.pdf`, `docs/tests_cache.pdf`
* **Memory Manager:** `docs/Contiguous Memory Management Simulator Report.pdf`, `docs/tests_contiguous.pdf`

## Prerequisites

* **C++ Compiler:** `g++` (Standard C++14 or higher).
* **Build System:** GNU `make`.
* **OS:** Linux or macOS (Recommended). Windows users should use WSL or MinGW.
