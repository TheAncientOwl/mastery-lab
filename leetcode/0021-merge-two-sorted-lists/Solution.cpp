#include "testing.hpp"

#include "ListNode.hpp"

using ListNode = TListNode<int>;

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        // 1. check for empty lists
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;

        // 2. decide head element
        ListNode* head = nullptr;
        if (list1->val < list2->val)
        {
            head = list1;
            list1 = list1->next;
        }
        else
        {
            head = list2;
            list2 = list2->next;
        }

        // 3. merge lists
        ListNode* curr{head};
        while (list1 && list2)
        {
            if (list1->val < list2->val)
            {
                curr->next = list1;
                curr = list1;
                list1 = list1->next;
            }
            else
            {
                curr->next = list2;
                curr = list2;
                list2 = list2->next;
            }
        }

        // 4. deal with remaining parts if list sizes !=
        if (list1)
        {
            curr->next = list1;
        }

        if (list2)
        {
            curr->next = list2;
        }

        // 5. GG easy
        return head;
    }
};

int main()
{
    {
        std::println("Example 1");
        auto const list1 = LinkedList<int>{1, 2, 4}.release();
        auto const list2 = LinkedList<int>{1, 3, 4}.release();
        auto const expected = LinkedList<int>({1, 1, 2, 3, 4, 4});
        auto const actual = LinkedList<int>{Solution{}.mergeTwoLists(list1, list2)};
        EXPECT_EQ(actual, expected);
    }
    {
        std::println("Example 2");
        auto const list1 = LinkedList<int>{}.release();
        auto const list2 = LinkedList<int>{}.release();
        auto const expected = LinkedList<int>({});
        auto const actual = LinkedList<int>{Solution{}.mergeTwoLists(list1, list2)};
        EXPECT_EQ(actual, expected);
    }
    {
        std::println("Example 3");
        auto const list1 = LinkedList<int>{1}.release();
        auto const list2 = LinkedList<int>{}.release();
        auto const expected = LinkedList<int>({1});
        auto const actual = LinkedList<int>{Solution{}.mergeTwoLists(list1, list2)};
        EXPECT_EQ(actual, expected);
    }
    {
        std::println("Example 4");
        auto const list1 = LinkedList<int>{}.release();
        auto const list2 = LinkedList<int>{1}.release();
        auto const expected = LinkedList<int>({1});
        auto const actual = LinkedList<int>{Solution{}.mergeTwoLists(list1, list2)};
        EXPECT_EQ(actual, expected);
    }
    return 0;
}
