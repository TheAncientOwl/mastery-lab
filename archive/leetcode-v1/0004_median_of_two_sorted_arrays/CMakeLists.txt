file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0004_median_of_two_sorted_arrays ${SOURCE_FILES})

target_include_directories(Leetcode_0004_median_of_two_sorted_arrays PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0004_median_of_two_sorted_arrays PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0004_median_of_two_sorted_arrays)
