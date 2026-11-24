#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) { return {}; }
};

void expectTwoSumIndices(std::vector<int>& nums, int target, std::vector<int> expected)
{
    auto actual = Solution{}.twoSum(nums, target);
    std::sort(actual.begin(), actual.end());
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, FirstExample)
{
    std::vector<int> nums{2, 7, 11, 15};
    expectTwoSumIndices(nums, 9, {0, 1});
}

TEST(TwoSum, SecondExample)
{
    std::vector<int> nums{3, 2, 4};
    expectTwoSumIndices(nums, 6, {1, 2});
}

TEST(TwoSum, RepeatedValues)
{
    std::vector<int> nums{3, 3};
    expectTwoSumIndices(nums, 6, {0, 1});
}
