#include "testing.hpp" // IWYU pragma: keep

#include <algorithm>
#include <vector>

class Solution
{
public:
    [[nodiscard]] int removeElement(std::vector<int>& nums, int const val) noexcept
    {
        std::size_t left{0};
        std::size_t right{nums.size()};

        while (left < right)
        {
            if (nums[left] == val)
            {
                nums[left] = nums[right - 1];
                --right;
            }
            else
            {
                ++left;
            }
        }

        return static_cast<int>(left);
    }
};

TEST(RemoveElement, Example1)
{
    auto input_nums = std::vector<int>{3, 2, 2, 3};
    auto input_val = 3;

    auto expected = 2;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{2, 2};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example2)
{
    auto input_nums = std::vector<int>{0, 1, 2, 2, 3, 0, 4, 2};
    auto input_val = 2;

    auto expected = 5;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{0, 1, 4, 0, 3};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example3)
{
    auto input_nums = std::vector<int>{1};
    auto input_val = 1;

    auto expected = 0;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example4)
{
    auto input_nums = std::vector<int>{2};
    auto input_val = 3;

    auto expected = 1;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{2};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example5)
{
    auto input_nums = std::vector<int>{3, 3};
    auto input_val = 5;

    auto expected = 2;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{3, 3};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example6)
{
    auto input_nums = std::vector<int>{2, 2, 3};
    auto input_val = 2;

    auto expected = 1;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{3};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveElement, Example7)
{
    auto input_nums = std::vector<int>{2, 2, 3};
    auto input_val = 3;

    auto expected = 2;
    auto actual = Solution{}.removeElement(input_nums, input_val);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{2, 2};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    std::sort(actual_nums_prefix.begin(), actual_nums_prefix.end());
    std::sort(expected_nums.begin(), expected_nums.end());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}
