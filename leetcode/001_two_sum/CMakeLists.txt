file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_001_two_sum ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(Leetcode_001_two_sum PRIVATE
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Leetcode_001_two_sum)
