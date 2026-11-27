#include "testing.hpp" // IWYU pragma: keep

#include <vector>

class Solution
{
public:
    [[nodiscard]] constexpr int searchInsert(std::vector<int> const& nums, int const target) const
    {
        if (nums.empty())
        {
            return 0;
        }

        std::size_t left{0};
        std::size_t right{nums.size() - 1};

        while (left < right)
        {
            std::size_t const mid{left + (right - left) / 2};

            if (nums[mid] == target)
            {
                return static_cast<int>(mid);
            }

            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        std::size_t const insert_idx{(nums[left] < target) ? (left + 1) : left};
        return static_cast<int>(insert_idx);
    }
};

TEST(SearchInsertPosition, Example1)
{
    auto input_nums = std::vector<int>{1, 3, 5, 6};
    auto input_target = 5;

    auto expected = 2;
    auto actual = Solution{}.searchInsert(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(SearchInsertPosition, Example2)
{
    auto input_nums = std::vector<int>{1, 3, 5, 6};
    auto input_target = 2;

    auto expected = 1;
    auto actual = Solution{}.searchInsert(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(SearchInsertPosition, Example3)
{
    auto input_nums = std::vector<int>{1, 3, 5, 6};
    auto input_target = 7;

    auto expected = 4;
    auto actual = Solution{}.searchInsert(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}
