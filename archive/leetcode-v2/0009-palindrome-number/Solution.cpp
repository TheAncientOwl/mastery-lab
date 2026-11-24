#include "testing.hpp"

class Solution
{
public:
    bool isPalindrome(int const x)
    {
        if (x < 0 || (x != 0 && x % 10 == 0))
        {
            return false;
        }

        std::uint64_t x_copy = x;
        std::uint64_t x_reversed = x_copy % 10;
        x_copy /= 10;

        while (x_copy > 0)
        {
            x_reversed = x_reversed * 10 + x_copy % 10;
            x_copy /= 10;
        }

        return x == x_reversed;
    }
};

int main()
{
    {
        auto const expected = true;
        auto const result = Solution{}.isPalindrome(121);
        EXPECT_EQ(result, expected);
    }
    {
        auto const expected = true;
        auto const result = Solution{}.isPalindrome(121);
        EXPECT_EQ(result, expected);
    }
    {
        auto const expected = false;
        auto const result = Solution{}.isPalindrome(-121);
        EXPECT_EQ(result, expected);
    }
    {
        auto const expected = false;
        auto const result = Solution{}.isPalindrome(10);
        EXPECT_EQ(result, expected);
    }
    {
        auto const expected = true;
        auto const result = Solution{}.isPalindrome(0);
        EXPECT_EQ(result, expected);
    }
    return 0;
}
