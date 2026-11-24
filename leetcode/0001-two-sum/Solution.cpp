#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {}
};

TEST(TwoSum, Example1)
{
    auto input_nums = std::vector<int>{2, 7, 11, 15};
    auto input_target = 9;

    auto expected = std::vector<int>{0, 1};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, Example2)
{
    auto input_nums = std::vector<int>{3, 2, 4};
    auto input_target = 6;

    auto expected = std::vector<int>{1, 2};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, Example3)
{
    auto input_nums = std::vector<int>{3, 3};
    auto input_target = 6;

    auto expected = std::vector<int>{0, 1};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}
