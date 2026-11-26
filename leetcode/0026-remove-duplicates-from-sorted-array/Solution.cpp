#include "testing.hpp" // IWYU pragma: keep

#include <vector>

class Solution
{
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        int last_idx{0};

        for (std::size_t idx = 1; idx < nums.size(); ++idx)
        {
            if (nums[idx] != nums[last_idx])
            {
                nums[++last_idx] = nums[idx];
            }
        }

        return last_idx + 1;
    }
};

TEST(RemoveDuplicatesFromSortedArray, Example1)
{
    auto input_nums = std::vector<int>{1, 1, 2};

    auto expected = 2;
    auto actual = Solution{}.removeDuplicates(input_nums);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{1, 2};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}

TEST(RemoveDuplicatesFromSortedArray, Example2)
{
    auto input_nums = std::vector<int>{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    auto expected = 5;
    auto actual = Solution{}.removeDuplicates(input_nums);
    EXPECT_EQ(actual, expected);
    auto expected_nums = std::vector<int>{0, 1, 2, 3, 4};
    ASSERT_GE(input_nums.size(), expected_nums.size());
    auto actual_nums_prefix =
        std::vector<int>(input_nums.begin(), input_nums.begin() + expected_nums.size());
    EXPECT_EQ(actual_nums_prefix, expected_nums);
}
