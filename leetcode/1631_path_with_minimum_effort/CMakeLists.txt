file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1631_path_with_minimum_effort ${SOURCE_FILES})

target_include_directories(Leetcode_1631_path_with_minimum_effort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1631_path_with_minimum_effort PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1631_path_with_minimum_effort)
