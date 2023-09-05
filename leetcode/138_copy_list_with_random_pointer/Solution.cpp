#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

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
        const auto c_out_head = new Node{ head->val };
        old_to_new.emplace(head, c_out_head);

        // create new list and fill map
        auto dummy{ c_out_head };
        for (auto it = head->next; it != nullptr; it = it->next)
        {
            // make node & link list
            auto new_node = new Node{ it->val };
            dummy->next = new_node;
            dummy = new_node;

            // fill map
            old_to_new.emplace(it, new_node);
        }

        // fill in the random nodes
        for (auto new_it = c_out_head, old_it = head; new_it != nullptr && old_it != nullptr; new_it = new_it->next, old_it = old_it->next)
        {
            new_it->random = old_it->random == nullptr ? nullptr : old_to_new[old_it->random];
        }

        return c_out_head;
    }
};

TEST(Leetcode_138_copy_list_with_random_pointer, test01)
{
    // Test it on https://leetcode.com/problems/copy-list-with-random-pointer/... :)
}
