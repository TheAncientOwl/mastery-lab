file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0905_sort_array_by_parity ${SOURCE_FILES})

target_include_directories(Leetcode_0905_sort_array_by_parity PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0905_sort_array_by_parity PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0905_sort_array_by_parity)
