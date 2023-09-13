#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    int candy(const std::vector<int>& ratings)
    {
        auto out{ 1 }, up{ 0 }, peak{ 0 }, down{ 0 };

        for (auto i = 1ul; i < ratings.size(); i++)
        {
            auto prev{ ratings[i - 1] };
            auto curr{ ratings[i] };

            if (prev < curr)
            {
                up++;
                down = 0;
                peak = up;
                out += up + 1;
            }
            else if (prev == curr)
            {
                up = 0;
                down = 0;
                peak = 0;
                out++;
            }
            else
            {
                up = 0;
                down++;
                out += down + 1;

                if (peak >= down)
                {
                    out--;
                }
            }
        }

        return out;
    }
};

TEST(Leetcode_0135_candy, test01)
{
    const std::vector<int> in{ 1, 0, 2 };
    const auto expected{ 5 };
    const auto out(Solution{}.candy(in));

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0135_candy, test02)
{
    const std::vector<int> in{ 1, 2, 2 };
    const auto expected{ 4 };
    const auto out(Solution{}.candy(in));

    EXPECT_EQ(out, expected);
}
