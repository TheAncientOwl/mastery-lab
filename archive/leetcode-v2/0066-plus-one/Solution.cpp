#include <algorithm>
#include <vector>

#include "testing.hpp"

class Solution
{
public:
    std::vector<int> plusOne(std::vector<int> const& digits)
    {
        std::vector<int> out{};
        out.reserve(digits.size() + 1);

        std::uint8_t carry{1};
        std::for_each(std::rbegin(digits), std::rend(digits), [&carry, &out](int digit) {
            digit += carry;
            out.push_back(digit % 10);
            carry = digit / 10;
        });
        if (carry)
        {
            out.push_back(1);
        }

        std::reverse(out.begin(), out.end());

        return out;
    }
};

int main()
{
    {
        auto const digits = std::vector{1, 2, 3};
        auto const expected = std::vector{1, 2, 4};
        auto const actual = Solution{}.plusOne(digits);
        EXPECT_EQ(actual, expected);
    }
    {
        auto const digits = std::vector{4, 3, 2, 1};
        auto const expected = std::vector{4, 3, 2, 2};
        auto const actual = Solution{}.plusOne(digits);
        EXPECT_EQ(actual, expected);
    }
    {
        auto const digits = std::vector{9};
        auto const expected = std::vector{1, 0};
        auto const actual = Solution{}.plusOne(digits);
        EXPECT_EQ(actual, expected);
    }

    return 0;
}
