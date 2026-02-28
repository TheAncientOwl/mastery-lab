cmake_minimum_required(VERSION 3.20)

project(26_remove_duplicates_from_sorted_array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(26_remove_duplicates_from_sorted_array
    Solution.cpp
)

# Include shared testing utilities
target_include_directories(26_remove_duplicates_from_sorted_array
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
)
