#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <string_view>
#include <functional>

class Solution
{
public:
    std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets)
    {
        std::unordered_map<std::string_view, std::vector<std::string_view>> tickets_graph{};

        for (const auto& ticket : tickets)
        {
            tickets_graph[ticket[0]].push_back(ticket[1]);
        }

        for (auto& [_, destinations] : tickets_graph)
        {
            std::sort(destinations.begin(), destinations.end(), std::greater<std::string_view>());
        }

        std::vector<std::string> itinerary{};
        const std::function<void(std::string_view)> dfs = [&](std::string_view airport) {
            while (!tickets_graph[airport].empty())
            {
                auto next{ tickets_graph[airport].back() };
                tickets_graph[airport].pop_back();
                dfs(next);
            }
            itinerary.emplace_back(airport);
            };

        dfs("JFK");
        std::reverse(itinerary.begin(), itinerary.end());

        return itinerary;
    }
};

TEST(Leetcode_0332_reconstruct_itinerary, test01)
{
    const std::vector<std::vector<std::string>> in{ {"MUC","LHR"}, {"JFK","MUC"}, {"SFO","SJC"}, {"LHR","SFO"} };
    const std::vector<std::string> expected{ "JFK", "MUC", "LHR", "SFO", "SJC" };
    const auto out{ Solution{}.findItinerary(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0332_reconstruct_itinerary, test02)
{
    const std::vector<std::vector<std::string>> in{ { "JFK", "SFO" }, { "JFK", "ATL" }, { "SFO", "ATL" }, { "ATL", "JFK" }, { "ATL", "SFO" } };
    const std::vector<std::string> expected{ "JFK", "ATL", "JFK", "SFO", "ATL", "SFO" };
    const auto out{ Solution{}.findItinerary(in) };

    EXPECT_EQ(out, expected);
}
