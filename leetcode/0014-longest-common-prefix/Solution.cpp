#include "testing.hpp" // IWYU pragma: keep

#include <algorithm>
#include <ranges>
#include <string>

#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr std::string longestCommonPrefix(std::vector<std::string> const& strs) const
    {
        if (strs.empty())
        {
            return {};
        }

        auto const min_length{std::ranges::min(strs, {}, &std::string::length).length()};

        for (std::size_t col_idx = 0; col_idx < min_length; ++col_idx)
        {
            for (std::size_t str_idx = 1; str_idx < strs.size(); ++str_idx)
            {
                if (strs[0][col_idx] != strs[str_idx][col_idx])
                {
                    return strs[0].substr(0, col_idx);
                }
            }
        }

        return strs[0].substr(0, min_length);
    }
};

TEST(LongestCommonPrefix, Example1)
{
    auto const input_strs =
        std::vector<std::string>{std::string{"flower"}, std::string{"flow"}, std::string{"flight"}};

    auto const expected = std::string{"fl"};
    auto const actual = Solution{}.longestCommonPrefix(input_strs);
    EXPECT_EQ(actual, expected);
}

TEST(LongestCommonPrefix, Example2)
{
    auto const input_strs =
        std::vector<std::string>{std::string{"dog"}, std::string{"racecar"}, std::string{"car"}};

    auto const expected = std::string{""};
    auto const actual = Solution{}.longestCommonPrefix(input_strs);
    EXPECT_EQ(actual, expected);
}
