cmake_minimum_required(VERSION 3.20)

project(0027_remove_element LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/GoogleTest.cmake)

add_executable(0027_remove_element
    Solution.cpp
)

target_link_libraries(0027_remove_element PRIVATE GTest::gtest_main leetcode_common)

include(GoogleTest)
gtest_discover_tests(0027_remove_element)
