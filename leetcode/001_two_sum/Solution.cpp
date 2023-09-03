#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target) const
    {
        std::vector<int> out{};

        std::unordered_map<int, int> complements{ {target - nums.front(), 0} }; // complement value -> position
        for (auto i = 1ul, end = nums.size(); i < end; i++)
        {
            const auto it = complements.find(nums[i]);

            if (it != complements.end())
            {
                out.push_back(it->second);
                out.push_back(i);
                break;
            }

            complements.emplace(target - nums[i], i);
        }

        return out;
    }
};

TEST(Leetcode_001_two_sum, test01)
{
    const std::vector<int> in{ 2, 7, 11, 15 };
    const int target{ 9 };

    const std::vector<int> expected{ 0, 1 };

    const auto out = Solution{}.twoSum(in, target);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_001_two_sum, test02)
{
    const std::vector<int> in{ 3, 2, 4 };
    const int target{ 6 };

    const std::vector<int> expected{ 1, 2 };

    const auto out = Solution{}.twoSum(in, target);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_001_two_sum, test03)
{
    const std::vector<int> in{ 3, 3 };
    const int target{ 6 };

    const std::vector<int> expected{ 0, 1 };

    const auto out = Solution{}.twoSum(in, target);

    EXPECT_EQ(out, expected);
}
