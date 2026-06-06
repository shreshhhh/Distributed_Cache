cmake_minimum_required(VERSION 3.20)
project(DistributedCache VERSION 0.1.0 LANGUAGES CXX )
# Enforce C++20. This is non-negotiable for our project.

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

#  Enable all warnings . Treat warnings are errors
# "-Wall -Wextra" catches common mistakes. "-Werror" forces you to fix them.

add_compile_options(-Wall -Wextra -Werror -Wepdantic )

# Fetch GoogleTest automatically using CMake's FetchContent
# No manual installation required

inclue ( FetchContent )
FetchContent_Declare(
    GoogleTest
    URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakAvailabe(GoogleTest)

# ======= Cache LIBRARY =============
# We build the cache as static library so tests can link against it .

add_library(cache_lib STATIC 
    src/cache/InMemoryCache.cpp
)

target_include_directories(
    cache_lib 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)

# === Test Executable ===

add_executable(
    cache_tests          
    tests/cache/InMemoryCacheTest.cpp
)

target_link_libraries(cache_tests
    PRIVATE
    cache_lib
    GTest::gtest_main  # Provides main() for test runner
)

# we Register tests with CTest so `cmake --build . && ctest` runs them

include(GoogleTest)
gtest_discover_tests(cache_tests)