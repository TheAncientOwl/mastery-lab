#include <vector>
#include "testing.hpp"

class Solution
{
public:
    int searchInsert(std::vector<int> const& nums, int const target)
    {
        int left{0};
        int right{static_cast<int>(nums.size())};

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (target < nums[mid])
            {
                right = mid;
            }
            else if (target > nums[mid])
            {
                left = mid + 1;
            }
            else
            {
                return mid;
            }
        }

        return left;
    }
};

int main()
{
    {
        auto const nums = std::vector{1, 3, 5, 6};
        EXPECT_EQ(Solution{}.searchInsert(nums, 5), 2);
    }
    {
        auto const nums = std::vector{1, 3, 5, 6};
        EXPECT_EQ(Solution{}.searchInsert(nums, 2), 1);
    }
    {
        auto const nums = std::vector{1, 3, 5, 6};
        EXPECT_EQ(Solution{}.searchInsert(nums, 7), 4);
    }
    return 0;
}
