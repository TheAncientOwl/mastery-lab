import unittest

from logic_fetch import extract_problem_name, generate_unit_tests


class GenerateUnitTestsTests(unittest.TestCase):
    def test_extracts_problem_slug_from_url(self):
        self.assertEqual(
            extract_problem_name("https://leetcode.com/problems/two-sum/description/"),
            "two-sum",
        )

    def test_generates_tests_from_vector_and_scalar_examples(self):
        code = """
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        return {};
    }
};
"""
        content = """
<pre><strong>Example 1:</strong><br><strong>Input:</strong> nums = [2,7,11,15], target = 9<br><strong>Output:</strong> [0,1]<br><strong>Explanation:</strong> example</pre>
<pre><strong>Example 2:</strong><br><strong>Input:</strong> nums = [3,2,4], target = 6<br><strong>Output:</strong> [1,2]</pre>
"""

        tests = generate_unit_tests(
            code, "[2,7,11,15]\n9\n[3,2,4]\n6", content, "Two Sum"
        )

        self.assertIn("TEST(TwoSum, Example1)", tests)
        self.assertIn("TEST(TwoSum, Example2)", tests)
        self.assertIn("std::vector<int>{2, 7, 11, 15}", tests)
        self.assertIn("Solution{}.twoSum(input_nums, input_target)", tests)
        self.assertIn("auto expected = std::vector<int>{1, 2};", tests)
        self.assertIn("EXPECT_EQ(actual, expected);", tests)

    def test_extracts_examples_from_paragraph_markup(self):
        code = """
class Solution {
public:
    bool isPalindrome(int x) {
        return false;
    }
};
"""
        content = """
<p><strong>Example 1:</strong></p>
<p><strong>Input:</strong> x = 121</p>
<p><strong>Output:</strong> true</p>
<p><strong>Explanation:</strong> It reads the same both ways.</p>
<p><strong>Example 2:</strong></p>
<p><strong>Input:</strong> x = -121</p>
<p><strong>Output:</strong> false</p>
"""

        tests = generate_unit_tests(code, "121\n-121", content)

        self.assertIn("EXPECT_EQ(actual, expected);", tests)
        self.assertIn("auto expected = true;", tests)
        self.assertIn("auto expected = false;", tests)

    def test_stops_example_output_before_constraints(self):
        code = """
class Solution {
public:
    bool isValid(std::string s) {
        return false;
    }
};
"""
        content = """
<pre><strong>Example 1:</strong><br><strong>Input:</strong> s = "()"<br><strong>Output:</strong> true<br><strong>Explanation:</strong> valid</pre>
<pre><strong>Example 2:</strong><br><strong>Input:</strong> s = "(]"<br><strong>Output:</strong> false<br><br><br><br><br><br>&nbsp;<br><br><br> Constraints: <br><br><br>1 &lt;= s.length &lt;= 104</pre>
"""

        tests = generate_unit_tests(code, '"()"\n"(]"', content)

        self.assertIn("auto expected = true;", tests)
        self.assertIn("auto expected = false;", tests)

    def test_generates_assertion_for_in_place_vector_output(self):
        code = """
class Solution {
public:
    void merge(std::vector<int>& nums, int count) {
    }
};
"""
        content = """
<pre><strong>Example 1:</strong><br><strong>Input:</strong> nums = [1,0], count = 1<br><strong>Output:</strong> nums = [1,2]<br><strong>Explanation:</strong> example</pre>
"""

        tests = generate_unit_tests(
            code, "[1,0]\n1", content
        )

        self.assertIn("Solution{}.merge(input_nums, input_count);", tests)
        self.assertIn("auto expected = std::vector<int>{1, 2};", tests)
        self.assertIn("EXPECT_EQ(input_nums, expected);", tests)

    def test_generates_nested_vector_of_strings(self):
        code = """
class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& values) {
        return {};
    }
};
"""
        content = """
<pre><strong>Example 1:</strong><br><strong>Input:</strong> values = ["flower","flow","flight"]<br><strong>Output:</strong> "fl"</pre>
"""

        tests = generate_unit_tests(
            code, '["flower","flow","flight"]', content
        )

        self.assertIn(
            'std::vector<std::string>{std::string{"flower"}, '
            'std::string{"flow"}, std::string{"flight"}}',
            tests,
        )
        self.assertIn('auto expected = std::string{"fl"};', tests)

    def test_rejects_unmatched_inputs_and_outputs(self):
        code = """
class Solution {
public:
    int answer(int value) {
        return value;
    }
};
"""
        content = (
            "<pre><strong>Example 1:</strong><br>"
            "<strong>Output:</strong> 1</pre>"
        )

        with self.assertRaisesRegex(ValueError, "match LeetCode example inputs"):
            generate_unit_tests(code, "", content)

    def test_reports_unsupported_linked_list_cases(self):
        code = """
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return head;
    }
};
"""
        content = """
<pre><strong>Example 1:</strong><br><strong>Input:</strong> head = [1,2]<br><strong>Output:</strong> [2,1]</pre>
"""

        with self.assertRaisesRegex(ValueError, "Unsupported C\\+\\+ test value type"):
            generate_unit_tests(code, "[1,2]", content)


if __name__ == "__main__":
    unittest.main()
