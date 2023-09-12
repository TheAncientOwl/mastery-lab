file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0001_two_sum ${SOURCE_FILES})

target_include_directories(Leetcode_0001_two_sum PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0001_two_sum PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0001_two_sum)
