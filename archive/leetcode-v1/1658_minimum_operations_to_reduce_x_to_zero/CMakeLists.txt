file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1658_minimum_operations_to_reduce_x_to_zero ${SOURCE_FILES})

target_include_directories(Leetcode_1658_minimum_operations_to_reduce_x_to_zero PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1658_minimum_operations_to_reduce_x_to_zero PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1658_minimum_operations_to_reduce_x_to_zero)
