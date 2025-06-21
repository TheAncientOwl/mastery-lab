file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_1359_count_all_valid_pickup_and_delivery_options ${SOURCE_FILES})

target_include_directories(Leetcode_1359_count_all_valid_pickup_and_delivery_options PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

target_link_libraries(Leetcode_1359_count_all_valid_pickup_and_delivery_options PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

include(GoogleTest)
gtest_discover_tests(Leetcode_1359_count_all_valid_pickup_and_delivery_options)
