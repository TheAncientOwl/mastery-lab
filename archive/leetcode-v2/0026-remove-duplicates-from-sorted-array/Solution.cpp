#include "testing.hpp"
#include <vector>

class Solution
{
public:
    int removeDuplicates(std::vector<int> &nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        int base_idx = 0;
        for (int idx = 1; idx < nums.size(); idx++)
        {
            if (nums[base_idx] != nums[idx])
            {
                base_idx++;
                nums[base_idx] = nums[idx];
            }
        }
        return base_idx + 1;
    }
};

int main()
{
    {
        auto nums = std::vector{1, 2};
        auto const expected_res = 2;
        auto const expected_nums = std::vector{1, 2};
        auto const actual = Solution{}.removeDuplicates(nums);
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{1, 1, 2};
        auto const expected_res = 2;
        auto const expected_nums = std::vector{1, 2};
        auto const actual = Solution{}.removeDuplicates(nums);
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        auto const expected_res = 5;
        auto const expected_nums = std::vector{0, 1, 2, 3, 4};
        auto const actual = Solution{}.removeDuplicates(nums);
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4};
        auto const expected_res = 5;
        auto const expected_nums = std::vector{0, 1, 2, 3, 4};
        auto const actual = Solution{}.removeDuplicates(nums);
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{1, 1};
        auto const expected_res = 1;
        auto const expected_nums = std::vector{1};
        auto const actual = Solution{}.removeDuplicates(nums);
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    return 0;
}
