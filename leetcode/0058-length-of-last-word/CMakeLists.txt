cmake_minimum_required(VERSION 3.20)

project(0058_length_of_last_word LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/GoogleTest.cmake)

add_executable(0058_length_of_last_word
    Solution.cpp
)

target_link_libraries(0058_length_of_last_word PRIVATE GTest::gtest_main leetcode_common)

include(GoogleTest)
gtest_discover_tests(0058_length_of_last_word)
