#include <vector>
#include "testing.hpp"

class Solution
{
public:
    std::vector<int> getRow(std::size_t const desired_row_index)
    {
        std::vector<int> row(desired_row_index + 1, 0);

        for (std::size_t row_index = 0; row_index <= desired_row_index; ++row_index)
        {
            for (int item_index = row_index - 1; item_index > 0; --item_index)
            {
                row[item_index] += row[item_index - 1];
            }
            row[row_index] = 1;
        }

        return row;
    }
};

int main()
{
    {
        auto const expected = std::vector<int>{1, 3, 3, 1};
        EXPECT_EQ(Solution{}.getRow(3), expected);
    }
    {
        auto const expected = std::vector<int>{1, 2, 1};
        EXPECT_EQ(Solution{}.getRow(2), expected);
    }
    {
        auto const expected = std::vector<int>{1, 1};
        EXPECT_EQ(Solution{}.getRow(1), expected);
    }
    {
        auto const expected = std::vector<int>{1};
        EXPECT_EQ(Solution{}.getRow(0), expected);
    }
    return 0;
}
