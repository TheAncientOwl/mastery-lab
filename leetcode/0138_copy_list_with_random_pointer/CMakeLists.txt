file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_0138_copy_list_with_random_pointer ${SOURCE_FILES})

target_include_directories(Leetcode_0138_copy_list_with_random_pointer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_0138_copy_list_with_random_pointer PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_0138_copy_list_with_random_pointer)
