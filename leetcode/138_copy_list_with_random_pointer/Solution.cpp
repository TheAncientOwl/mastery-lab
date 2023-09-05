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

        std::unordered_map<Node*, std::size_t> old_nodes_to_idx{};
        std::vector<Node*> idx_to_new_nodes{};

        // create head and fill maps
        const auto c_out_head = new Node{ head->val };
        old_nodes_to_idx.emplace(head, 0);
        idx_to_new_nodes.push_back(c_out_head);

        // create empty list and fill 2 maps
        std::size_t current_idx{ 1 };
        auto dummy{ c_out_head };
        for (auto it = head->next; it != nullptr; it = it->next, current_idx++)
        {
            // make node & link list
            auto new_node = new Node{ it->val };
            dummy->next = new_node;
            dummy = new_node;

            // fill maps
            old_nodes_to_idx.emplace(it, current_idx);
            idx_to_new_nodes.push_back(new_node);
        }

        // fill in the random nodes
        for (auto new_it = c_out_head, old_it = head; new_it != nullptr && old_it != nullptr; new_it = new_it->next, old_it = old_it->next)
        {
            new_it->random = old_it->random == nullptr ? nullptr : idx_to_new_nodes[old_nodes_to_idx[old_it->random]];
        }

        return c_out_head;
    }
};

TEST(Leetcode_138_copy_list_with_random_pointer, test01)
{
    // Test it on https://leetcode.com/problems/copy-list-with-random-pointer/... :)
}
