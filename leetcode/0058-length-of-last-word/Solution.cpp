#include "testing.hpp"
#include <algorithm>
#include <string_view>

using namespace std::string_literals;

class SolutionV0
{
public:
    int lengthOfLastWord(std::string_view sv)
    {
        static auto constexpr c_space{' '};
        while (!sv.empty() && sv.back() == c_space)
        {
            sv.remove_suffix(1);
        }

        int length{0};
        for (auto rit = sv.rbegin(); rit != sv.rend(); ++rit)
        {
            if (*rit == c_space)
            {
                break;
            }
            ++length;
        }
        return length;
    }
};

class SolutionV1
{
public:
    int lengthOfLastWord(std::string_view sv)
    {
        static auto constexpr c_space{' '};
        while (!sv.empty() && sv.back() == c_space)
        {
            sv.remove_suffix(1);
        }

        auto const space_it = std::find(sv.rbegin(), sv.rend(), c_space);
        return space_it == sv.rend() ? sv.length() : std::distance(sv.rbegin(), space_it);
    }
};

using Solution = SolutionV1;

int main()
{
    {
        auto const str = ""s;
        auto const expected = 0;
        auto const actual = Solution{}.lengthOfLastWord(str);
        EXPECT_EQ(actual, expected);
    }
    {
        auto const str = "   d   "s;
        auto const expected = 1;
        auto const actual = Solution{}.lengthOfLastWord(str);
        EXPECT_EQ(actual, expected);
    }
    {
        auto const str = "  ddd  d   "s;
        auto const expected = 1;
        auto const actual = Solution{}.lengthOfLastWord(str);
        EXPECT_EQ(actual, expected);
    }
    {
        auto const str = "Hello World"s;
        auto const expected = 5;
        auto const actual = Solution{}.lengthOfLastWord(str);
        EXPECT_EQ(actual, expected);
    }
    return 0;
}
