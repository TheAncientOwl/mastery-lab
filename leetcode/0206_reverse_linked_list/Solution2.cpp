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
        ListNode* prev{ nullptr };
        ListNode* next{ nullptr };

        while (head)
        {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }
};

TEST(Leetcode_0206_reverse_linked_list, test01_2)
{
    // Test it on https://leetcode.com/problems/reverse-linked-list/... :)
}
