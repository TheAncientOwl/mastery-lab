#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    int countOrders(int n)
    {
        static constexpr auto MOD{ 1000000007 };

        uint64_t count{ 1 };
        for (auto i = 2; i <= n; i++)
        {
            count = (count * (2 * i - 1) * i) % MOD;
        }
        return (int) count;
    }
};

TEST(Leetcode_1359_count_all_valid_pickup_and_delivery_options, test01)
{
    const int in{ 1 };
    const int expected{ 1 };
    const int out{ Solution{}.countOrders(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1359_count_all_valid_pickup_and_delivery_options, test02)
{
    const int in{ 2 };
    const int expected{ 6 };
    const int out{ Solution{}.countOrders(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1359_count_all_valid_pickup_and_delivery_options, test03)
{
    const int in{ 3 };
    const int expected{ 90 };
    const int out{ Solution{}.countOrders(in) };

    EXPECT_EQ(out, expected);
}
