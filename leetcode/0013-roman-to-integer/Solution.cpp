#include "testing.hpp" // IWYU pragma: keep

#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr std::uint16_t romanToInt(std::string_view const str) const noexcept
    {
        ///
        /// @note LeetCode guarantee, number in range [1, 3999]
        ///
        /// if (str.empty())
        /// {
        ///     return 0;
        /// }

        std::int16_t res{0};

        std::int16_t prev{convert(str.front())};
        for (std::size_t idx = 1; idx < str.length(); ++idx)
        {
            auto const curr{convert(str[idx])};
            if (prev < curr)
            {
                res -= prev;
            }
            else
            {
                res += prev;
            }
            prev = curr;
        }
        res += prev;

        return res;
    }

private:
    [[nodiscard]] static constexpr std::int16_t convert(const char symbol) noexcept
    {
        // clang-format off
        switch (symbol)
        {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        // clang-format on
        return 0;
    }
};

TEST(RomanToInteger, Example1)
{
    auto const input_str = std::string{"III"};

    auto const expected = 3;
    auto const actual = Solution{}.romanToInt(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(RomanToInteger, Example2)
{
    auto const input_str = std::string{"LVIII"};

    auto const expected = 58;
    auto const actual = Solution{}.romanToInt(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(RomanToInteger, Example3)
{
    auto const input_str = std::string{"MCMXCIV"};

    auto const expected = 1994;
    auto const actual = Solution{}.romanToInt(input_str);
    EXPECT_EQ(actual, expected);
}
