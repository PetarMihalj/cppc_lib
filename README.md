# C++ concurrency library (cppc\_lib)



### Installation

1. Clone the repository and position yourself in it
2. Run `cmake .`
3. Run `make cppc_lib` or `make cppc_lib run_tests`, depending on whether you want to build a test suite
4. If you made a test suite, run it by executing the `run_tests` executable which has been created

### Usage

- Include the `./include/cppc.h` file as a header
- Link the generated `./libcppc_lib.a` when linking your program
- Link the `pthread` library when linking your program (`-pthread` flag on most compilers)
