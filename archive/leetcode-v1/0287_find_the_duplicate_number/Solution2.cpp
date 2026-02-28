#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    int findDuplicate(const std::vector<int>& nums)
    {
        auto slow{ nums[0] };
        auto fast{ nums[0] };

        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        slow = nums[0];
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};

TEST(Leetcode_0287_find_the_duplicate_number, test01_2)
{
    const std::vector<int> in{ 1, 3, 4, 2, 2 };
    const auto expected{ 2 };
    const auto out{ Solution{}.findDuplicate(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0287_find_the_duplicate_number, test02_2)
{
    const std::vector<int> in{ 3, 1, 3, 4, 2 };
    const auto expected{ 3 };
    const auto out{ Solution{}.findDuplicate(in) };

    EXPECT_EQ(out, expected);
}
