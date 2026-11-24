#pragma once

#include <cstdlib>
#include <iostream>

#include "operators.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

struct ExpectEqStream
{
    bool failed;

    explicit ExpectEqStream(bool f) : failed(f) {}

    template <typename T>
    ExpectEqStream &operator<<(const T &value)
    {
        if (failed)
        {
            std::cout << value;
        }
        return *this;
    }
};

#define EXPECT_EQ(actual, expected) \
    ([&]() -> ExpectEqStream {                                                                                      \
        auto _actual = (actual);                                                                                     \
        auto _expected = (expected);                                                                                 \
        if (!(_actual == _expected)) {                                                                               \
            std::cout << RED << "EXPECT_EQ failed at " << __FILE__ << ":" << __LINE__ << RESET << std::endl;     \
            std::cout << "  Actual:   " << _actual << std::endl;                                                   \
            std::cout << "  Expected: " << _expected << std::endl;                                                 \
            return ExpectEqStream(true);                                                                             \
        } else {                                                                                                     \
            std::cout << GREEN << "EXPECT_EQ passed at " << __FILE__ << ":" << __LINE__ << RESET << std::endl;   \
            return ExpectEqStream(false);                                                                            \
        } })()
