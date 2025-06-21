#include <gtest/gtest.h>

class Node
{
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node* copyRandomList(Node* head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        // interweave old list with new nodes
        for (auto curr_old = head; curr_old != nullptr; curr_old = curr_old->next->next)
        {
            auto new_node{ new Node{ curr_old->val } };

            new_node->next = curr_old->next;
            curr_old->next = new_node;
        }

        // make the random links for the new nodes
        for (auto curr_old = head; curr_old != nullptr; curr_old = curr_old->next->next)
        {
            auto new_node{ curr_old->next };

            new_node->random = curr_old->random ? curr_old->random->next : nullptr;
        }

        // separate lists
        const auto c_out_head{ head->next };
        head->next = c_out_head->next;

        for (auto curr_old = head->next, curr_new = c_out_head; curr_old != nullptr; curr_old = curr_old->next)
        {
            auto new_node{ curr_old->next };
            curr_old->next = new_node->next;

            curr_new->next = new_node;
            curr_new = new_node;
        }

        return c_out_head;
    }
};

TEST(Leetcode_138_copy_list_with_random_pointer, test01_2)
{
    // Test it on https://leetcode.com/problems/copy-list-with-random-pointer/... :)
}
