# Week 5: Code Optimization and Performance Profiling

## Project Overview
This project demonstrates an optimized C++ particle simulation. It focuses on improving execution efficiency, memory management, and code quality while maintaining correct program behavior.

## Objectives
- Identify potential performance bottlenecks.
- Optimize memory allocation and data processing.
- Measure program execution time.
- Maintain correctness and reliable output.

## Files
- main.cpp: C++ source code for the particle simulation.
- README.md: Project documentation and instructions.

## Requirements
- C++ compiler supporting C++17 (GCC, Clang, or MSVC).
- Optional profiling tools: gprof or Valgrind.

## Compilation
Using GCC:
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o week5_simulation
```

## Run the Program
```bash
./week5_simulation
```

For a smaller test:
```bash
./week5_simulation 1000 10
```
The optional arguments are particle count and simulation steps.

## Optimization Techniques
1. `vector::reserve()` reduces repeated memory reallocations.
2. Particles are updated in place without creating temporary vectors.
3. `std::vector` provides contiguous storage and automatic memory management.
4. Final metrics are calculated in a single pass.
5. A fixed random seed makes simulation results reproducible.
6. Compiler optimization is enabled with `-O2`.

## Performance Profiling
For GCC gprof profiling:
```bash
g++ -std=c++17 -O2 -pg main.cpp -o week5_profile
./week5_profile 200000 500
gprof ./week5_profile gmon.out > profile.txt
```

For Valgrind memory checking, if installed:
```bash
valgrind --leak-check=full ./week5_simulation 10000 50
```

## Testing
- Run a small simulation and check the output.
- Run the same input twice and compare the average speed and checksum.
- Check that zero particles or zero steps produce an error.
- Compare runtime with a reference implementation if available.

## Results
The program prints average speed, checksum, and elapsed time. Record actual measurements from your system before claiming performance improvements. No benchmark results are assumed in this README.

## Conclusion
This project demonstrates practical C++ optimization techniques, memory management, testing, and performance profiling. It strengthens understanding of writing efficient and maintainable C++ programs.