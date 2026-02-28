#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums)
    {
        auto left{ 0ul };
        auto right{ nums.size() - 1 };

        while (left < right)
        {
            while (left < right && nums[left] % 2 == 0)
            {
                left++;
            }

            while (left < right && nums[right] % 2 != 0)
            {
                right--;
            }

            std::swap(nums[left], nums[right]);
        }

        return nums;
    }
};

TEST(Leetcode_0905_sort_array_by_parity, test01_2)
{
    std::vector<int> in{ 3, 1, 2, 4 };
    const std::vector<int> expected{ 4, 2, 1, 3 };
    const auto out{ Solution{}.sortArrayByParity(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0905_sort_array_by_parity, test02_2)
{
    std::vector<int> in{ 0 };
    const std::vector<int> expected{ 0 };
    const auto out{ Solution{}.sortArrayByParity(in) };

    EXPECT_EQ(out, expected);
}
