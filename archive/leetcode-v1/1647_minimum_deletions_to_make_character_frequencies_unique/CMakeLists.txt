file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique ${SOURCE_FILES})

target_include_directories(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique)
