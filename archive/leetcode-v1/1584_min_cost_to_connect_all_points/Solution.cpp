#include <gtest/gtest.h>

#include <vector>
#include <queue>

class Solution
{
public:
    using Point = std::pair<int, int>;

public:
    int minCostConnectPoints(const std::vector<std::vector<int>>& points)
    {
        const auto c_points_count{ points.size() };
        std::vector<bool> visited(c_points_count, false);
        std::vector<int> distances(c_points_count, INT_MAX);

        auto cmp = [](Point left, Point right) { return left.first > right.first; };
        std::priority_queue<Point, std::vector<Point>, decltype(cmp)> min_heap{};

        distances[0] = 0;
        min_heap.emplace(0, 0);

        auto total_weight{ 0 };
        while (!min_heap.empty())
        {
            const auto [min_weight, top_point_idk] = min_heap.top();
            min_heap.pop();

            if (visited[top_point_idk] || distances[top_point_idk] < min_weight)
            {
                continue;
            }

            visited[top_point_idk] = true;
            total_weight += min_weight;

            for (auto point_idx = 0ul; point_idx < c_points_count; point_idx++)
            {
                if (!visited[point_idx])
                {
                    const auto new_distance{ manhattan_distance(points[top_point_idk], points[point_idx]) };
                    if (new_distance < distances[point_idx])
                    {
                        distances[point_idx] = new_distance;
                        min_heap.emplace(new_distance, point_idx);
                    }
                }
            }
        }

        return total_weight;
    }

private:
    int manhattan_distance(const std::vector<int>& p1, const std::vector<int>& p2)
    {
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
};

TEST(Leetcode_1584_min_cost_to_connect_all_points, test01)
{
    const std::vector<std::vector<int>> in{ { 0, 0 }, { 2, 2 }, { 3, 10 }, { 5, 2 }, { 7, 0 } };
    const auto expected{ 20 };
    const auto out{ Solution{}.minCostConnectPoints(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1584_min_cost_to_connect_all_points, test02)
{
    const std::vector<std::vector<int>> in{ { 3, 12 }, { -2, 5 }, { -4, 1 } };
    const auto expected{ 18 };
    const auto out{ Solution{}.minCostConnectPoints(in) };

    EXPECT_EQ(out, expected);
}
