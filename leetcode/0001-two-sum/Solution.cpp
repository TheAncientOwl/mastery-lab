#include "testing.hpp"

#include <unordered_map>
#include <vector>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> const &nums, int const target)
    {
        std::unordered_map<int, int> complement_to_index{};

        for (int index = 0; index < nums.size(); ++index)
        {
            auto const it = complement_to_index.find(nums[index]);
            if (it != complement_to_index.end())
            {
                return {it->second, index};
            }

            complement_to_index.emplace(target - nums[index], index);
        }

        return {0, 0}; // Irellevant -> You may assume that each input would have exactly one solution
    }
};

int main()
{
    {
        std::cout << ">> Example 1" << std::endl;
        auto const nums = std::vector{2, 7, 11, 15};
        auto const target = 9;
        auto const expected = std::vector{0, 1};
        auto const result = Solution{}.twoSum(nums, target);
        EXPECT_EQ(result, expected);
        std::cout << std::endl;
    }
    {
        std::cout << ">> Example 1" << std::endl;
        auto const nums = std::vector{3, 2, 4};
        auto const target = 6;
        auto const expected = std::vector{1, 2};
        auto const result = Solution{}.twoSum(nums, target);
        EXPECT_EQ(result, expected);
        std::cout << std::endl;
    }
    {
        std::cout << ">> Example 1" << std::endl;
        auto const nums = std::vector{3, 3};
        auto const target = 6;
        auto const expected = std::vector{0, 1};
        auto const result = Solution{}.twoSum(nums, target);
        EXPECT_EQ(result, expected);
        std::cout << std::endl;
    }
    return 0;
}
