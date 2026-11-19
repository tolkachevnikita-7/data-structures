cmake_minimum_required(VERSION 3.14)
project(StackProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_executable(stack_tests 
    test/test.cpp 
    include/Stack.h
    include/Queue.h
    include/BracketsSolver.h
    include/tmatrix.h
)

target_link_libraries(stack_tests PRIVATE gtest gtest_main)

enable_testing()
add_test(NAME AllTests COMMAND stack_tests)