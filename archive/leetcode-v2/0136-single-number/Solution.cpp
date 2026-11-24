#include <vector>
#include "testing.hpp"

class Solution
{
public:
    int singleNumber(std::vector<int> const& nums)
    {
        int num{0};
        for (auto x : nums)
            num ^= x;
        return num;
    }
};

int main()
{
    {
        auto const nums = std::vector{2, 2, 1};
        EXPECT_EQ(Solution{}.singleNumber(nums), 1);
    }
    {
        auto const nums = std::vector{4, 1, 2, 1, 2};
        EXPECT_EQ(Solution{}.singleNumber(nums), 4);
    }
    {
        auto const nums = std::vector{1};
        EXPECT_EQ(Solution{}.singleNumber(nums), 1);
    }
    return 0;
}
