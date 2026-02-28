#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    /**
     * @brief solve using sliding window
    */
    int minOperations(const std::vector<int>& nums, int x)
    {
        auto target{ 0 };
        for (auto num : nums)
        {
            target += num;
        }

        target -= x;

        if (target == 0)
        {
            return nums.size();
        }

        auto max_length{ 0 };
        auto current_sum{ 0 };
        auto left_pos{ 0 };

        for (auto right_pos = 0; right_pos < nums.size(); ++right_pos)
        {
            current_sum += nums[right_pos];

            while (left_pos <= right_pos && current_sum > target)
            {
                current_sum -= nums[left_pos];
                left_pos++;
            }

            if (current_sum == target)
            {
                max_length = std::max(max_length, right_pos - left_pos + 1);
            }
        }

        return max_length ? nums.size() - max_length : -1;
    }
};

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test01_2)
{
    const std::vector<int> in_nums{ 1, 1, 4, 2, 3 };
    const auto in_x{ 5 };
    const auto expected{ 2 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test02_2)
{
    const std::vector<int> in_nums{ 5, 6, 7, 8, 9 };
    const auto in_x{ 4 };
    const auto expected{ -1 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test03_2)
{
    const std::vector<int> in_nums{ 3, 2, 20, 1, 1, 3 };
    const auto in_x{ 10 };
    const auto expected{ 5 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test04_2)
{
    const std::vector<int> in_nums{ 1, 1 };
    const auto in_x{ 3 };
    const auto expected{ -1 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}
