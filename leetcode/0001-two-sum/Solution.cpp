#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> const& nums, int target) { return {}; }
};

TEST(TwoSum, FirstExample)
{
    std::vector<int> const nums{2, 7, 11, 15};
    auto actual = Solution{}.twoSum(nums, 9);
    std::vector<int> const expected{0, 1};
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, SecondExample)
{
    std::vector<int> const nums{3, 2, 4};
    auto actual = Solution{}.twoSum(nums, 6);
    std::vector<int> const expected{1, 2};
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, RepeatedValues)
{
    std::vector<int> const nums{3, 3};
    auto actual = Solution{}.twoSum(nums, 6);
    std::vector<int> const expected{0, 1};
    EXPECT_EQ(actual, expected);
}
