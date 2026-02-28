#include <gtest/gtest.h>

#include <vector>
#include <climits>
#include <queue>

class Solution
{
public:
    int minimumEffortPath(const std::vector<std::vector<int>>& heights)
    {
        const auto c_rows{ heights.size() };
        const auto c_cols{ heights[0].size() };

        std::vector<std::vector<int>> distances(c_rows, std::vector<int>(c_cols, INT_MAX));
        const auto cmp = [](const std::tuple<int, int, int>& lhs, const std::tuple<int, int, int>& rhs) { return std::get<0>(lhs) > std::get<0>(rhs); };
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(cmp)> min_heap{};

        min_heap.emplace(0, 0, 0);
        distances[0][0] = 0;

        const int c_directions[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        while (!min_heap.empty())
        {
            const auto [effort, x, y] = min_heap.top();
            min_heap.pop();

            if (effort > distances[x][y])
            {
                continue;
            }

            if (x == c_rows - 1 && y == c_cols - 1)
            {
                return effort;
            }

            for (const auto& direction : c_directions)
            {
                const auto new_x = x + direction[0];
                const auto new_y = y + direction[1];

                if (new_x >= 0 && new_x < c_rows && new_y >= 0 && new_y < c_cols)
                {
                    const auto new_effort{ std::max(effort, abs(heights[x][y] - heights[new_x][new_y])) };
                    if (new_effort < distances[new_x][new_y])
                    {
                        distances[new_x][new_y] = new_effort;
                        min_heap.emplace(new_effort, new_x, new_y);
                    }
                }
            }
        }

        return -1;
    }
};

TEST(Leetcode_1631_path_with_minimum_effort, test01)
{
    const std::vector<std::vector<int>> in{
        { 1, 2, 2 },
        { 3, 8, 2 },
        { 5, 3, 5 },
    };
    const auto expected{ 2 };
    const auto out{ Solution{}.minimumEffortPath(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1631_path_with_minimum_effort, test02)
{
    const std::vector<std::vector<int>> in{
        { 1, 2, 3 },
        { 3, 8, 4 },
        { 5, 3, 5 },
    };
    const auto expected{ 1 };
    const auto out{ Solution{}.minimumEffortPath(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1631_path_with_minimum_effort, test03)
{
    const std::vector<std::vector<int>> in{
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 1 },
        { 1, 2, 1, 2, 1 },
        { 1, 2, 1, 2, 1 },
        { 1, 1, 1, 2, 1 },
    };
    const auto expected{ 0 };
    const auto out{ Solution{}.minimumEffortPath(in) };

    EXPECT_EQ(out, expected);
}
