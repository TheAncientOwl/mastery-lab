#include "testing.hpp"

#include "ListNode.hpp"

using ListNode = TListNode<int>;

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        ListNode* curr{head};
        while (curr->next != nullptr)
        {
            ListNode* next{curr->next};
            if (next != nullptr && curr->val == next->val)
            {
                curr->next = next->next;
                delete next;
            }
            else
            {
                curr = next;
            }
        }

        return head;
    }
};

int main()
{
    {
        auto const head = LinkedList<int>{1, 1, 2}.release();
        auto const expected = LinkedList<int>{1, 2};
        auto const actual = LinkedList<int>{Solution{}.deleteDuplicates(head)};
        EXPECT_EQ(actual, expected);
    }
    {
        auto const head = LinkedList<int>{1, 1, 2, 2}.release();
        auto const expected = LinkedList<int>{1, 2};
        auto const actual = LinkedList<int>{Solution{}.deleteDuplicates(head)};
        EXPECT_EQ(actual, expected);
    }
    return 0;
}
