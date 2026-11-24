cmake_minimum_required(VERSION 3.20)

project(0118_pascals_triangle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(0118_pascals_triangle
    Solution.cpp
)

# Include shared testing utilities
target_include_directories(0118_pascals_triangle
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
)
