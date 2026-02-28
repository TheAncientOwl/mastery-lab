cmake_minimum_required(VERSION 3.20)

project(58_length_of_last_word LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(58_length_of_last_word
    Solution.cpp
)

# Include shared testing utilities
target_include_directories(58_length_of_last_word
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
)
