#include <assert.h>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>

#include "testing.hpp"

using namespace std::string_literals;

class Solution
{
public:
    bool isValid(std::string_view sv)
    {
        std::stack<std::int8_t> seq{};
        seq.push(0);

        seq.push(convert(sv.front()));
        sv.remove_prefix(1);

        for (auto const chr : sv)
        {
            auto const code = convert(chr);

            auto const codeOpen = isOpen(code);

            if (seq.empty() && !codeOpen)
            {
                return false;
            }

            auto const topClosed = isClosed(seq.top());

            // ][
            if (codeOpen || topClosed)
            {
                seq.push(code);
            }
            // () || [] || {} || (] || [) || ...
            else if (!topClosed && !codeOpen)
            {
                // (] || [) || ...
                if (-code != seq.top())
                {
                    return false;
                }
                // () || [] || {}
                else
                {
                    if (!seq.empty())
                    {
                        seq.pop();
                    }
                }
            }
        }

        return seq.size() == 1;
    }

private:
    inline std::int8_t convert(char const chr) noexcept
    {
        switch (chr)
        {
        case '(':
            return 1;
        case ')':
            return -1;
        case '{':
            return 2;
        case '}':
            return -2;
        case '[':
            return 3;
        case ']':
            return -3;
        }
        assert(false && "Should not reach here");
        return 0;
    }

    inline bool isOpen(std::int8_t code) noexcept { return code > 0; }
    inline bool isClosed(std::int8_t code) noexcept { return code < 0; }
};

int main()
{
    {
        std::cout << "Example 1" << std::endl;
        auto const in = "()"s;
        auto const expected = true;
        auto const actual = Solution{}.isValid(in);
        EXPECT_EQ(actual, expected);
    }
    {
        std::cout << "Example 2" << std::endl;
        auto const in = "()[]{}"s;
        auto const expected = true;
        auto const actual = Solution{}.isValid(in);
        EXPECT_EQ(actual, expected);
    }
    {
        std::cout << "Example 3" << std::endl;
        auto const in = "(]"s;
        auto const expected = false;
        auto const actual = Solution{}.isValid(in);
        EXPECT_EQ(actual, expected);
    }
    {
        std::cout << "Example 4" << std::endl;
        auto const in = "([])"s;
        auto const expected = true;
        auto const actual = Solution{}.isValid(in);
        EXPECT_EQ(actual, expected);
    }
    {
        std::cout << "Example 5" << std::endl;
        auto const in = "([)]"s;
        auto const expected = false;
        auto const actual = Solution{}.isValid(in);
        EXPECT_EQ(actual, expected);
    }
    return 0;
}
