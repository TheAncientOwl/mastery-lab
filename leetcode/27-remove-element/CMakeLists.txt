cmake_minimum_required(VERSION 3.20)

project(27_remove_element LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(27_remove_element
    Solution.cpp
)

# Include shared testing utilities
target_include_directories(27_remove_element
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
)
