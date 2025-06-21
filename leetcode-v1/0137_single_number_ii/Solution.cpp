#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    int singleNumber(const std::vector<int>& nums)
    {
        int out{ 0 };

        for (int i = 0; i < 32; ++i)
        {
            int sum{ 0 };
            for (const auto num : nums)
            {
                sum += num >> i & 1;
            }
            sum %= 3;
            out |= sum << i;
        }

        return out;
    }
};

TEST(Leetcode_0137_single_number_ii, test01)
{
    const std::vector<int> in{ 2, 2, 3, 2 };
    const auto expected{ 3 };
    const auto out{ Solution{}.singleNumber(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0137_single_number_ii, test02)
{
    const std::vector<int> in{ 0, 1, 0, 1, 0, 1, 99 };
    const auto expected{ 99 };
    const auto out{ Solution{}.singleNumber(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0137_single_number_ii, test03)
{
    const std::vector<int> in{ 0, 1, 0, 1, 1 };
    const auto expected{ 0 };
    const auto out{ Solution{}.singleNumber(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0137_single_number_ii, test04)
{
    const std::vector<int> in{ 0, -1, 0, -1, 0, -1, 2, 2, 2, -99 };
    const auto expected{ -99 };
    const auto out{ Solution{}.singleNumber(in) };

    EXPECT_EQ(out, expected);
}
