file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1584_min_cost_to_connect_all_points ${SOURCE_FILES})

target_include_directories(Leetcode_1584_min_cost_to_connect_all_points PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1584_min_cost_to_connect_all_points PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1584_min_cost_to_connect_all_points)
