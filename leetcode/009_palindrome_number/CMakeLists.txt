file(GLOB SOURCE_FILES *.cpp)
add_executable(Leetcode_009_palindrome_number ${SOURCE_FILES})

target_link_libraries(Leetcode_009_palindrome_number PRIVATE
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Leetcode_009_palindrome_number)
