file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0287_find_the_duplicate_number ${SOURCE_FILES})

target_include_directories(Leetcode_0287_find_the_duplicate_number PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0287_find_the_duplicate_number PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0287_find_the_duplicate_number)
