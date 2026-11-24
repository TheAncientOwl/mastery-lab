#include "testing.hpp"

#include <string>
#include <vector>

class Solution
{
public:
    std::string longestCommonPrefix(std::vector<std::string> const &strs)
    {
        if (strs.size() == 1)
        {
            return strs[0];
        }

        for (std::size_t col_idx = 0; col_idx < strs[0].size(); ++col_idx)
        {
            for (std::size_t row_idx = 1; row_idx < strs.size(); ++row_idx)
            {
                if (strs[row_idx].length() <= col_idx || strs[row_idx][col_idx] != strs[0][col_idx])
                {
                    return std::string(strs[0].begin(), strs[0].begin() + col_idx);
                }
            }
        }

        return strs[0];
    }
};

int main()
{
    {
        auto const strs = std::vector<std::string>{"flower", "flow", "flight"};
        auto const expected = std::string{"fl"};
        auto const result = Solution{}.longestCommonPrefix(strs);
        EXPECT_EQ(result, expected);
    }
    {
        auto const strs = std::vector<std::string>{"dog", "racecar", "car"};
        auto const expected = std::string{""};
        auto const result = Solution{}.longestCommonPrefix(strs);
        EXPECT_EQ(result, expected);
    }
    {
        auto const strs = std::vector<std::string>{"flower", "flower", "flower", "flower"};
        auto const expected = std::string{"flower"};
        auto const result = Solution{}.longestCommonPrefix(strs);
        EXPECT_EQ(result, expected);
    }
    return 0;
}
