#include <vector>
#include "testing.hpp"

class Solution
{
public:
    std::vector<std::vector<int>> generate(std::size_t const num_rows)
    {
        std::vector<std::vector<int>> out_rows{};
        out_rows.reserve(num_rows);
        out_rows.push_back({1});

        for (std::size_t row_num{2}; row_num <= num_rows; ++row_num)
        {
            auto const row_index{row_num - 1};
            auto const prev_row_index{row_index - 1};

            auto& row = out_rows.emplace_back();
            row.reserve(row_index + 1);

            row.push_back(1);
            for (std::size_t item_idx{1}; item_idx < row_num - 1; ++item_idx)
            {
                row.push_back(
                    out_rows[prev_row_index][item_idx - 1] + out_rows[prev_row_index][item_idx]);
            }
            row.push_back(1);
        }

        return out_rows;
    }
};

int main()
{
    {
        auto const expected =
            std::vector<std::vector<int>>{{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};
        EXPECT_EQ(Solution{}.generate(5), expected);
    }
    {
        auto const expected = std::vector<std::vector<int>>{{1}, {1, 1}};
        EXPECT_EQ(Solution{}.generate(2), expected);
    }
    {
        auto const expected = std::vector<std::vector<int>>{{1}};
        EXPECT_EQ(Solution{}.generate(1), expected);
    }
    return 0;
}
