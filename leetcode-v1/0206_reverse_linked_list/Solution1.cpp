#include <gtest/gtest.h>


struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode* reverseList(ListNode* head)
    {
        return reverse(head, nullptr);
    }

private:
    ListNode* reverse(ListNode* curr, ListNode* prev)
    {
        if (!curr)
        {
            return prev;
        }
        else
        {
            auto next{ curr->next };

            curr->next = prev;

            return reverse(next, curr);
        }
    }
};

TEST(Leetcode_0206_reverse_linked_list, test01_1)
{
    // Test it on https://leetcode.com/problems/reverse-linked-list/... :)
}
