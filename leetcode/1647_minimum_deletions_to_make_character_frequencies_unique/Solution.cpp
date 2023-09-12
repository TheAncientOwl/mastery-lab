#include <gtest/gtest.h>

#include <functional>
#include <algorithm>
#include <string_view>
#include <array>

class Solution
{
public:
    int minDeletions(std::string_view str)
    {
        constexpr auto c_alphabet_size{ 'z' - 'a' + 1 };
        std::array<int, c_alphabet_size> occurences{};

        for (auto chr : str)
        {
            occurences[chr - 'a']++;
        }

        std::sort(occurences.begin(), occurences.end(), std::greater<int>());

        auto out{ 0 };
        for (std::size_t i = 0; i < c_alphabet_size && occurences[i] > 0; i++)
        {
            for (std::size_t j = i + 1; j < c_alphabet_size && occurences[j] > 0 && occurences[i] == occurences[j]; occurences[j++]--, out++);
        }

        return out;
    }
};

TEST(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique, test01)
{
    const auto in{ "aab" };
    const auto expected{ 0 };
    const auto out{ Solution{}.minDeletions(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique, test02)
{
    const auto in{ "aaabbbcc" };
    const auto expected{ 2 };
    const auto out{ Solution{}.minDeletions(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique, test03)
{
    const auto in{ "ceabaacb" };
    const auto expected{ 2 };
    const auto out{ Solution{}.minDeletions(in) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_1647_minimum_deletions_to_make_character_frequencies_unique, test04)
{
    const auto in{ "abcabc" };
    const auto expected{ 3 };
    const auto out{ Solution{}.minDeletions(in) };

    EXPECT_EQ(out, expected);
}
