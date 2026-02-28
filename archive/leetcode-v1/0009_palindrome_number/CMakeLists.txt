file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0009_palindrome_number ${SOURCE_FILES})

target_include_directories(Leetcode_0009_palindrome_number PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0009_palindrome_number PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0009_palindrome_number)
