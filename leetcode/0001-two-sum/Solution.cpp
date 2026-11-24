#include "testing.hpp" // IWYU pragma: keep

#include <cstdint>

#include <unordered_map>
#include <vector>

class Solution
{
public:
    std::vector<std::int32_t> twoSum(std::vector<std::int32_t> const& nums, std::int32_t const target)
    {
        std::unordered_map<std::int32_t, std::int32_t> value_to_index{};

        for (std::int32_t idx = 0; idx < nums.size(); ++idx)
        {
            auto const looking_for{target - nums[idx]};
            auto const it = value_to_index.find(looking_for);
            if (it != value_to_index.end())
            {
                return {it->second, idx};
            }
            value_to_index.emplace(nums[idx], idx);
        }

        return {};
    }
};

TEST(TwoSum, Example1)
{
    auto input_nums = std::vector<int>{2, 7, 11, 15};
    auto input_target = 9;

    auto expected = std::vector<std::int32_t>{0, 1};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, Example2)
{
    auto input_nums = std::vector<int>{3, 2, 4};
    auto input_target = 6;

    auto expected = std::vector<std::int32_t>{1, 2};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}

TEST(TwoSum, Example3)
{
    auto input_nums = std::vector<int>{3, 3};
    auto input_target = 6;

    auto expected = std::vector<std::int32_t>{0, 1};
    auto actual = Solution{}.twoSum(input_nums, input_target);
    EXPECT_EQ(actual, expected);
}
