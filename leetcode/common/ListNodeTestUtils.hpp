#pragma once

#include <initializer_list>
#include <memory>
#include <unordered_set>
#include <vector>

namespace ListNodeTestUtils {

template <typename Node>
class Arena
{
public:
    Arena() = default;
    Arena(Arena const&) = delete;
    Arena& operator=(Arena const&) = delete;

    ~Arena()
    {
        for (auto* node : m_nodes)
        {
            delete node;
        }
    }

    Node* make_list(std::initializer_list<int> values)
    {
        Node* head = nullptr;
        Node** tail = &head;
        for (auto value : values)
        {
            auto node = std::make_unique<Node>(value);
            m_nodes.insert(node.get());
            *tail = node.release();
            tail = &(*tail)->next;
        }
        return head;
    }

    void track(Node* head)
    {
        std::unordered_set<Node*> visited;
        while (head && visited.insert(head).second)
        {
            m_nodes.insert(head);
            head = head->next;
        }
    }

    std::vector<int> values(Node const* head) const
    {
        std::vector<int> result;
        std::unordered_set<Node const*> visited;
        while (head && visited.insert(head).second)
        {
            result.push_back(head->val);
            head = head->next;
        }
        return result;
    }

private:
    std::unordered_set<Node*> m_nodes;
};

} // namespace ListNodeTestUtils
