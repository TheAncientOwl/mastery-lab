cmake_minimum_required(VERSION 3.20)

project(14_longest_common_prefix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(14_longest_common_prefix
    Solution.cpp
)

# Include shared testing utilities
target_include_directories(14_longest_common_prefix
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
)
