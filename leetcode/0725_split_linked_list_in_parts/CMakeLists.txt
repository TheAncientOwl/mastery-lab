file(GLOB SOURCE_FILES *.cpp)
add_executable(Leetcode_0725_split_linked_list_in_parts ${SOURCE_FILES})

target_link_libraries(Leetcode_0725_split_linked_list_in_parts PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

target_include_directories(Leetcode_0725_split_linked_list_in_parts PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

include(GoogleTest)
gtest_discover_tests(Leetcode_0725_split_linked_list_in_parts)
