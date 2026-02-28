#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    int findDuplicate(const std::vector<int>& nums)
    {
        std::vector<bool> found(nums.size(), false);

        for (const auto num : nums)
        {
            if (found[num])
            {
                return num;
            }

            found[num] = true;
        }

        return -1;
    }
};

TEST(Leetcode_0287_find_the_duplicate_number, test01_1)
{
    const std::vector<int> in{ 1, 3, 4, 2, 2 };
    const auto expected{ 2 };
    const auto out{ Solution{}.findDuplicate(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0287_find_the_duplicate_number, test02_1)
{
    const std::vector<int> in{ 3, 1, 3, 4, 2 };
    const auto expected{ 3 };
    const auto out{ Solution{}.findDuplicate(in) };

    EXPECT_EQ(out, expected);
}
