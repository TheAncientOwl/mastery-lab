#include <gtest/gtest.h>

#include <unordered_map>

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

        std::unordered_map<Node*, Node*> old_to_new{};

        // create new head and fill map
        const auto c_out_head{ new Node{ head->val } };
        old_to_new.emplace(head, c_out_head);

        // create new list and fill map
        for (auto curr_old = head->next, curr_new = c_out_head; curr_old != nullptr; curr_old = curr_old->next)
        {
            // make node & link list
            auto new_node{ new Node{ curr_old->val } };
            curr_new->next = new_node;
            curr_new = new_node;

            // fill map
            old_to_new.emplace(curr_old, new_node);
        }

        // fill in the random nodes
        for (auto curr_new = c_out_head, curr_old = head; curr_new != nullptr && curr_old != nullptr; curr_new = curr_new->next, curr_old = curr_old->next)
        {
            curr_new->random = curr_old->random ? old_to_new[curr_old->random] : nullptr;
        }

        return c_out_head;
    }
};

TEST(Leetcode_138_copy_list_with_random_pointer, test01_1)
{
    // Test it on https://leetcode.com/problems/copy-list-with-random-pointer/... :)
}
