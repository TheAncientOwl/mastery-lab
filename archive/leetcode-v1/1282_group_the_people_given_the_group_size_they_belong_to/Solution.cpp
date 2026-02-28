#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>

class Solution
{
public:
    std::vector<std::vector<int>> groupThePeople(const std::vector<int>& groupSizes)
    {
        std::vector<std::vector<int>> out{};

        std::unordered_map<int, std::vector<int>> groups{};

        for (auto i = 0ul, end = groupSizes.size(); i < end; i++)
        {
            const auto c_group_size{ groupSizes[i] };

            if (auto it = groups.find(c_group_size); it != groups.end())
            {
                if (it->second.size() + 1 > c_group_size)
                {
                    out.emplace_back(std::move(it->second));
                    it->second = std::vector<int>{ static_cast<int>(i) };
                }
                else
                {
                    it->second.push_back(i);
                }
            }
            else
            {
                groups[c_group_size].push_back(i);
            }
        }

        out.reserve(out.size() + groups.size());

        for (auto& group : groups)
        {
            out.emplace_back(std::move(group.second));
        }

        return out;
    }
};

TEST(Leetcode_1282_group_the_people_given_the_group_size_they_belong_to, test01)
{
    // Test it on https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/... :)
}
