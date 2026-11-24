#include "testing.hpp" // IWYU pragma: keep

class Solution
{
public:
    bool isPalindrome(std::int64_t const x)
    {
        if (x < 0 || (x > 0 && x % 10 == 0))
        {
            return false;
        }

        std::int64_t reversed_x{0};
        auto copy_x{x};
        while (copy_x > 0)
        {
            (reversed_x *= 10) += copy_x % 10;
            copy_x /= 10;
        }

        return x == reversed_x;
    }
};

TEST(PalindromeNumber, Example1)
{
    auto input_x = 121;

    auto expected = true;
    auto actual = Solution{}.isPalindrome(input_x);
    EXPECT_EQ(actual, expected);
}

TEST(PalindromeNumber, Example2)
{
    auto input_x = -121;

    auto expected = false;
    auto actual = Solution{}.isPalindrome(input_x);
    EXPECT_EQ(actual, expected);
}

TEST(PalindromeNumber, Example3)
{
    auto input_x = 10;

    auto expected = false;
    auto actual = Solution{}.isPalindrome(input_x);
    EXPECT_EQ(actual, expected);
}
