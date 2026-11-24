#include "testing.hpp"
#include <algorithm>
#include <vector>

class Solution
{
public:
    int removeElement(std::vector<int> &nums, int const val)
    {
        int removed_count{0};
        int base_idx = 0;
        for (int idx = 0; idx < nums.size(); idx++)
        {
            if (nums[idx] != val)
            {
                nums[base_idx] = nums[idx];
                ++base_idx;
            }
            else
            {
                ++removed_count;
            }
        }

        return nums.size() - removed_count;
    }
};

int main()
{
    {
        auto nums = std::vector<int>{};
        auto const expected_res = 0;
        auto const val{3};
        auto const expected_nums = std::vector<int>{};
        auto const actual = Solution{}.removeElement(nums, val);
        std::sort(nums.begin(), nums.end());
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size" << "\n";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{3, 2, 2, 3};
        auto const expected_res = 2;
        auto const val{3};
        auto const expected_nums = std::vector{2, 2};
        auto const actual = Solution{}.removeElement(nums, val);
        std::sort(nums.begin(), nums.end());
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size" << "\n";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{3, 2, 3, 2, 3};
        auto const expected_res = 2;
        auto const val{3};
        auto const expected_nums = std::vector{2, 2};
        auto const actual = Solution{}.removeElement(nums, val);
        std::sort(nums.begin(), nums.end());
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size" << "\n";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }
    {
        auto nums = std::vector{3, 2, 3, 3, 3, 3, 3, 2, 3, 3, 3, 3};
        auto const expected_res = 2;
        auto const val{3};
        auto const expected_nums = std::vector{2, 2};
        auto const actual = Solution{}.removeElement(nums, val);
        std::sort(nums.begin(), nums.end());
        EXPECT_EQ(actual, expected_res) << "Missmatch in new size" << "\n";
        for (std::size_t idx = 0; idx < expected_nums.size(); ++idx)
        {
            EXPECT_EQ(nums[idx], expected_nums[idx]) << "index: " << idx << "\n";
        }
    }

    return 0;
}
