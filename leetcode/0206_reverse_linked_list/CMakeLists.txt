file(GLOB SOURCE_FILES *.cpp)
add_executable(Leetcode_0206_reverse_linked_list ${SOURCE_FILES})

target_link_libraries(Leetcode_0206_reverse_linked_list PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

target_include_directories(Leetcode_0206_reverse_linked_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

include(GoogleTest)
gtest_discover_tests(Leetcode_0206_reverse_linked_list)
