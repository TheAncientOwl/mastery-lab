file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1282_group_the_people_given_the_group_size_they_belong_to ${SOURCE_FILES})

target_include_directories(Leetcode_1282_group_the_people_given_the_group_size_they_belong_to PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1282_group_the_people_given_the_group_size_they_belong_to PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1282_group_the_people_given_the_group_size_they_belong_to)
