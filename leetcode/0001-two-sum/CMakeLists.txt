cmake_minimum_required(VERSION 3.20)

project(0001_two_sum LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/GoogleTest.cmake)

add_executable(0001_two_sum
    Solution.cpp
)

target_link_libraries(0001_two_sum PRIVATE GTest::gtest_main leetcode_common)

include(GoogleTest)
gtest_discover_tests(0001_two_sum)
