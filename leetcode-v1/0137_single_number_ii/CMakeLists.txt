file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0137_single_number_ii ${SOURCE_FILES})

target_include_directories(Leetcode_0137_single_number_ii PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0137_single_number_ii PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0137_single_number_ii)
