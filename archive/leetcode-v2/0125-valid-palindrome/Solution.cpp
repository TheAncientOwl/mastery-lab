#include <string_view>
#include "testing.hpp"

using namespace std::string_literals;

class Solution
{
public:
    bool isPalindrome(std::string_view sv)
    {
        while (sv.length() > 1)
        {
            if (!std::isalnum(sv.front()))
            {
                sv.remove_prefix(1);
                continue;
            }

            if (!std::isalnum(sv.back()))
            {
                sv.remove_suffix(1);
                continue;
            }

            if (std::toupper(sv.front()) != std::toupper(sv.back()))
            {
                return false;
            }

            sv.remove_prefix(1);
            sv.remove_suffix(1);
        }

        return true;
    }
};

int main()
{
    {
        auto const str = "A man, a plan, a canal: Panama"s;
        EXPECT_EQ(true, Solution{}.isPalindrome(str));
    }
    {
        auto const str = "race a car"s;
        EXPECT_EQ(false, Solution{}.isPalindrome(str));
    }
    {
        auto const str = " "s;
        EXPECT_EQ(true, Solution{}.isPalindrome(str));
    }
    {
        auto const str = "0P"s;
        EXPECT_EQ(false, Solution{}.isPalindrome(str));
    }
    return 0;
}
