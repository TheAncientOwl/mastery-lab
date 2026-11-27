#include "testing.hpp" // IWYU pragma: keep

#include <string>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr int lengthOfLastWord(std::string_view str) const noexcept
    {
        int idx{static_cast<int>(str.size()) - 1};
        while (idx >= 0 && str[idx] == ' ')
        {
            --idx;
        }

        auto const end_pos{idx};
        if (end_pos == -1)
        {
            return 0;
        }

        while (idx >= 0 && str[idx] != ' ')
        {
            --idx;
        }

        return end_pos == idx ? 1 : end_pos - idx;
    }
};

TEST(LengthOfLastWord, Example1)
{
    auto input_s = std::string{"Hello World"};

    auto expected = 5;
    auto actual = Solution{}.lengthOfLastWord(input_s);
    EXPECT_EQ(actual, expected);
}

TEST(LengthOfLastWord, Example2)
{
    auto input_s = std::string{"   fly me   to   the moon  "};

    auto expected = 4;
    auto actual = Solution{}.lengthOfLastWord(input_s);
    EXPECT_EQ(actual, expected);
}

TEST(LengthOfLastWord, Example3)
{
    auto input_s = std::string{"luffy is still joyboy"};

    auto expected = 6;
    auto actual = Solution{}.lengthOfLastWord(input_s);
    EXPECT_EQ(actual, expected);
}

TEST(LengthOfLastWord, Example4)
{
    auto input_s = std::string{"day"};

    auto expected = 3;
    auto actual = Solution{}.lengthOfLastWord(input_s);
    EXPECT_EQ(actual, expected);
}

TEST(LengthOfLastWord, Example5)
{
    auto input_s = std::string{"d"};

    auto expected = 1;
    auto actual = Solution{}.lengthOfLastWord(input_s);
    EXPECT_EQ(actual, expected);
}
