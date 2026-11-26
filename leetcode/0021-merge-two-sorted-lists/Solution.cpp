#include "testing.hpp" // IWYU pragma: keep

#include "ListNode.hpp"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        if (!list1 && !list2)
        {
            return nullptr;
        }

        if (list1 && !list2)
        {
            return list1;
        }

        if (!list1 && list2)
        {
            return list2;
        }

        ListNode* it1{list1};
        ListNode* it2{list2};

        ListNode* head{nullptr};
        if (it1->val < it2->val)
        {
            head = it1;
            it1 = it1->next;
        }
        else
        {
            head = it2;
            it2 = it2->next;
        }

        ListNode* curr{head};

        while (it1 && it2)
        {
            if (it1->val < it2->val)
            {
                curr->next = it1;
                it1 = it1->next;
            }
            else
            {
                curr->next = it2;
                it2 = it2->next;
            }

            curr = curr->next;
        }

        if (it1)
        {
            curr->next = it1;
        }
        else
        {
            curr->next = it2;
        }

        return head;
    }
};

TEST(MergeTwoSortedLists, Example1)
{
    ListNodeTestUtils::Arena<ListNode> list_nodes;
    auto input_list1 = list_nodes.make_list({1, 2, 4});
    auto input_list2 = list_nodes.make_list({1, 3, 4});

    auto expected = std::vector<int>{1, 1, 2, 3, 4, 4};
    auto actual = Solution{}.mergeTwoLists(input_list1, input_list2);
    list_nodes.track(actual);
    EXPECT_EQ(list_nodes.values(actual), expected);
}

TEST(MergeTwoSortedLists, Example2)
{
    ListNodeTestUtils::Arena<ListNode> list_nodes;
    auto input_list1 = list_nodes.make_list({});
    auto input_list2 = list_nodes.make_list({});

    auto expected = std::vector<int>{};
    auto actual = Solution{}.mergeTwoLists(input_list1, input_list2);
    list_nodes.track(actual);
    EXPECT_EQ(list_nodes.values(actual), expected);
}

TEST(MergeTwoSortedLists, Example3)
{
    ListNodeTestUtils::Arena<ListNode> list_nodes;
    auto input_list1 = list_nodes.make_list({});
    auto input_list2 = list_nodes.make_list({0});

    auto expected = std::vector<int>{0};
    auto actual = Solution{}.mergeTwoLists(input_list1, input_list2);
    list_nodes.track(actual);
    EXPECT_EQ(list_nodes.values(actual), expected);
}
