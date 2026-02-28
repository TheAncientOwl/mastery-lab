#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    std::vector<int> sortArrayByParity(const std::vector<int>& nums)
    {
        std::vector<int> out{};
        out.reserve(nums.size());

        for (auto num : nums)
        {
            if (num % 2 == 0)
            {
                out.push_back(num);
            }
        }

        for (auto num : nums)
        {
            if (num % 2 != 0)
            {
                out.push_back(num);
            }
        }

        return out;
    }
};

TEST(Leetcode_0905_sort_array_by_parity, test01_1)
{
    const std::vector<int> in{ 3, 1, 2, 4 };
    const std::vector<int> expected{ 2, 4, 3, 1 };
    const auto out{ Solution{}.sortArrayByParity(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0905_sort_array_by_parity, test02_1)
{
    const std::vector<int> in{ 0 };
    const std::vector<int> expected{ 0 };
    const auto out{ Solution{}.sortArrayByParity(in) };

    EXPECT_EQ(out, expected);
}
