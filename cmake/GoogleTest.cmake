if(NOT TARGET GTest::gtest_main)
    find_package(GTest CONFIG QUIET)
endif()

if(NOT TARGET GTest::gtest_main)
    if(NOT DEFINED FETCHCONTENT_BASE_DIR OR
       FETCHCONTENT_BASE_DIR STREQUAL "${CMAKE_BINARY_DIR}/_deps")
        set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/_deps-${CMAKE_GENERATOR}")
    endif()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()
