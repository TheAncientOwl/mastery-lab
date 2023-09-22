#include <gtest/gtest.h>

#include <string_view>

class Solution
{
public:
    bool isSubsequence(std::string_view s, std::string_view t)
    {
        auto i{ 0ul };

        for (auto j = 0ul; i < s.size() && j < t.size(); j++)
        {
            if (s[i] == t[j])
            {
                i++;
            }
        }

        return i == s.size();
    }
};

TEST(Leetcode_0392_is_subsequence, test01)
{
    const auto in1{ "abc" };
    const auto in2{ "ahbgdc" };
    const auto expected{ true };
    const auto out{ Solution{}.isSubsequence(in1, in2) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0392_is_subsequence, test02)
{
    const auto in1{ "axc" };
    const auto in2{ "ahbgdc" };
    const auto expected{ false };
    const auto out{ Solution{}.isSubsequence(in1, in2) };

    EXPECT_EQ(out, expected);
}
