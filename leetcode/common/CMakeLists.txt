add_library(leetcode_common INTERFACE)

target_include_directories(leetcode_common
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(leetcode_common_tests
    operators_test.cpp
    list_node_test_utils_test.cpp
)

target_link_libraries(leetcode_common_tests
    PRIVATE
        GTest::gtest_main
        leetcode_common
)

include(GoogleTest)
gtest_discover_tests(leetcode_common_tests)
