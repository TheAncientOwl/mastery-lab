file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1048_longest_string_chain ${SOURCE_FILES})

target_include_directories(Leetcode_1048_longest_string_chain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1048_longest_string_chain PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1048_longest_string_chain)
