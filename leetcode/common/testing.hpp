#pragma once

#include <cstdlib>
#include <iostream>

#include "operators.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define EXPECT_EQ(actual, expected)                                                                            \
    do                                                                                                         \
    {                                                                                                          \
        auto _actual = (actual);                                                                               \
        auto _expected = (expected);                                                                           \
        if (!(_actual == _expected))                                                                           \
        {                                                                                                      \
            std::cerr << RED << "EXPECT_EQ failed at " << __FILE__ << ":" << __LINE__ << RESET << std::endl;   \
            std::cerr << "  Actual:   " << _actual << std::endl;                                               \
            std::cerr << "  Expected: " << _expected << std::endl;                                             \
        }                                                                                                      \
        else                                                                                                   \
        {                                                                                                      \
            std::cerr << GREEN << "EXPECT_EQ passed at " << __FILE__ << ":" << __LINE__ << RESET << std::endl; \
        }                                                                                                      \
    } while (0)
