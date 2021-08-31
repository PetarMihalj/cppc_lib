# C++11 concurrency library (cppc\_lib)

A C++11 concurrency library which ports primitives available in later language standards.

### Why?

There are alternative implementations which I strongly suggest the reader to use.
Even though this library is covered by extensive tests,
its main purpose was for me to learn:
- standard library facilities (and implementing the missing ones)
- mutual exclusion primitives and how to use them to implement more advanced patterns
- usage of cmake and regression testing frameworks (gtest)

### Features

- mutex / shared mutex
- conditional variable
- unique lock / shared lock
- barrier
- semaphore

Check out the `./include/cppc.h` for further info and documentation.
You can find the use cases in `./tests/` folder.

### Installation

1. Clone the repository and position yourself in it
2. Run `cmake .`
3. Run `make cppc_lib` (without tests) or `make cppc_lib run_tests` (with test suite)
4. If you made a test suite, run it by executing the `./run_tests --gtest_repeat=10`
(some tests are nondeterministic, you can increase the number if you have time to spare)

### Usage

- Include the `./include/cppc.h` file as a header
- Link the generated `./libcppc_lib.a` when linking your program
- Link the `pthread` library when linking your program (`-pthread` flag on most compilers)
