#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>
#include <climits>

class Solution
{
public:
    /**
     * @brief solve using hashmaps
    */
    int minOperations(const std::vector<int>& nums, int x)
    {
        auto answer{ INT_MAX };

        // map the value of sum "from end to begin" we need to find 
        // to the (position + 1) aka the count of elements from the front in which the counterpart was found in the sum "from begin to end"
        std::unordered_map<int, int> need_to_count{};

        auto left_to_right{ 0 };
        for (int i = 0ul; i < nums.size(); i++)
        {
            left_to_right += nums[i];

            if (left_to_right < x)
            {
                need_to_count.emplace(x - left_to_right, i + 1);
            }
            else if (left_to_right == x)
            {
                answer = std::min(answer, static_cast<int>(i + 1));
            }
            else
            {
                break;
            }
        }

        auto right_to_left{ 0 };
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            const auto c_elements_count{ static_cast<int>(nums.size() - i) };

            right_to_left += nums[i];

            if (right_to_left < x)
            {
                const auto it = need_to_count.find(right_to_left);
                if (it != need_to_count.end() && it->second - 1 < i)
                {
                    answer = std::min(answer, it->second + c_elements_count);
                }
            }
            else if (right_to_left == x)
            {
                answer = std::min(answer, c_elements_count);
            }
            else
            {
                break;
            }
        }

        return answer == INT_MAX ? -1 : answer;
    }
};

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test01_1)
{
    const std::vector<int> in_nums{ 1, 1, 4, 2, 3 };
    const auto in_x{ 5 };
    const auto expected{ 2 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test02_1)
{
    const std::vector<int> in_nums{ 5, 6, 7, 8, 9 };
    const auto in_x{ 4 };
    const auto expected{ -1 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test03_1)
{
    const std::vector<int> in_nums{ 3, 2, 20, 1, 1, 3 };
    const auto in_x{ 10 };
    const auto expected{ 5 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1658_minimum_operations_to_reduce_x_to_zero, test04_1)
{
    const std::vector<int> in_nums{ 1, 1 };
    const auto in_x{ 3 };
    const auto expected{ -1 };
    const auto out{ Solution{}.minOperations(in_nums, in_x) };

    EXPECT_EQ(out, expected);
}
