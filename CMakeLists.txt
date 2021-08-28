cmake_minimum_required(VERSION 3.14)
project(cppc_lib)
set(CMAKE_CXX_STANDARD 17)

# GTEST

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES "src/*.cpp")
include_directories("include/")
link_libraries("pthread")

# OPTION: main

add_executable("main" "dev/main.cpp" ${SOURCES})

# OPTION: tests

enable_testing()
file(GLOB_RECURSE TESTFILES ${PROJECT_SOURCE_DIR}/tests *_test.cpp)
add_executable(run_tests ${TESTFILES} ${SOURCES})
target_link_libraries(run_tests gtest_main)
include(GoogleTest)
gtest_discover_tests(run_tests)
