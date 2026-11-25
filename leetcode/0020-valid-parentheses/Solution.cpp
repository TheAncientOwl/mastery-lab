#include "testing.hpp" // IWYU pragma: keep

#include <stack>
#include <string>
#include <string_view>

class Solution
{
public:
    [[nodiscard]] constexpr bool isValid(std::string_view const str) const
    {
        ///
        /// @note Leetcode guarantee: str.length >= 1
        ///
        /// if (str.empty())
        /// {
        ///     return true;
        /// }

        if (!isOpen(str.front()))
        {
            return false;
        }

        std::stack<char> stack{};
        stack.push(str.front());
        for (std::size_t idx = 1; idx < str.size(); ++idx)
        {
            auto const curr{str[idx]};

            if (isOpen(curr))
            {
                stack.push(curr);
                continue;
            }

            if (stack.empty() || !match(stack.top(), curr))
            {
                return false;
            }

            stack.pop();
        }

        return stack.empty();
    }

private:
    [[nodiscard]] constexpr static bool isOpen(char const paran) noexcept
    {
        return paran == '(' || paran == '[' || paran == '{';
    }

    [[nodiscard]] constexpr static bool match(char const open_paran, char const closed_paran) noexcept
    {
        return (open_paran == '(' && closed_paran == ')') ||
               (open_paran == '[' && closed_paran == ']') ||
               (open_paran == '{' && closed_paran == '}');
    }
};

TEST(ValidParentheses, Example1)
{
    auto const input_str = std::string{"()"};

    auto const expected = true;
    auto const actual = Solution{}.isValid(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(ValidParentheses, Example2)
{
    auto const input_str = std::string{"()[]{}"};

    auto const expected = true;
    auto const actual = Solution{}.isValid(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(ValidParentheses, Example3)
{
    auto const input_str = std::string{"(]"};

    auto const expected = false;
    auto const actual = Solution{}.isValid(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(ValidParentheses, Example4)
{
    auto const input_str = std::string{"([])"};

    auto const expected = true;
    auto const actual = Solution{}.isValid(input_str);
    EXPECT_EQ(actual, expected);
}

TEST(ValidParentheses, Example5)
{
    auto const input_str = std::string{"([)]"};

    auto const expected = false;
    auto const actual = Solution{}.isValid(input_str);
    EXPECT_EQ(actual, expected);
}
