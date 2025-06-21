#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int longestStrChain(std::vector<std::string>& words)
    {
        std::sort(words.begin(), words.end(), [](const std::string_view& lhs, const std::string_view& rhs) {
            return lhs.size() < rhs.size();
            });

        std::unordered_map<std::string, int> dp{};
        auto max_chain{ 0 };

        for (const auto& word : words)
        {
            auto& dp_val = dp[word];

            dp_val = 1;
            for (auto i = 0ul; i < word.size(); i++)
            {
                const std::string prev_word = word.substr(0, i) + word.substr(i + 1);
                if (const auto it = dp.find(prev_word); it != dp.end())
                {
                    dp_val = std::max(dp_val, it->second + 1);
                }
            }
            max_chain = std::max(max_chain, dp_val);
        }

        return max_chain;
    }
};

TEST(Leetcode_1048_longest_string_chain, test01)
{
    std::vector<std::string> in{ "a", "b", "ba", "bca", "bda", "bdca" };
    const auto expected{ 4 };
    const auto out{ Solution{}.longestStrChain(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1048_longest_string_chain, test02)
{
    std::vector<std::string> in{ "xbc", "pcxbcf", "xb", "cxbc", "pcxbc" };
    const auto expected{ 5 };
    const auto out{ Solution{}.longestStrChain(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1048_longest_string_chain, test03)
{
    std::vector<std::string> in{ "abcd", "dbqca" };
    const auto expected{ 1 };
    const auto out{ Solution{}.longestStrChain(in) };

    EXPECT_EQ(out, expected);
}
