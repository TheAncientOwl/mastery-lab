#include <gtest/gtest.h>

class Solution
{
public:
    bool isPalindrome(int x) const
    {
        if (x < 0 || (x != 0 && x % 10 == 0)) return false;

        int fast{ x };
        int slow{ x };
        int reversed_half{ 0 };

        while (fast)
        {
            reversed_half = reversed_half * 10 + slow % 10;
            slow /= 10;
            fast /= 100;
        }

        return slow == reversed_half || slow == reversed_half / 10;
    }
};

TEST(Leetcode_0009_palindrome_number, test01)
{
    const int in = 121;
    const bool expected = true;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test02)
{
    const int in = -121;
    const bool expected = false;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test03)
{
    const int in = 10;
    const bool expected = false;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test04)
{
    const int in = 1111;
    const bool expected = true;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test05)
{
    const int in = 1231;
    const bool expected = false;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test06)
{
    const int in = 21120;
    const bool expected = false;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0009_palindrome_number, test07)
{
    const int in = 0;
    const bool expected = true;
    const bool out = Solution{}.isPalindrome(in);

    EXPECT_EQ(out, expected);
}
