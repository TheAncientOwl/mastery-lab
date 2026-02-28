#include <gtest/gtest.h>

#include <vector>

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
    std::vector<ListNode*> splitListToParts(ListNode* head, std::size_t k)
    {
        const auto c_list_size{ getListSize(head) };

        std::vector<ListNode*> out{};
        out.reserve(k);

        const auto c_small_list_size{ static_cast<std::size_t>(c_list_size / k) };
        const auto c_big_list_size{ static_cast<std::size_t>(c_small_list_size + 1) };
        auto big_lists_count{ c_list_size % k };

        for (auto _ = 0ul; _ < k; _++)
        {
            auto current_size{ big_lists_count > 0 ? c_big_list_size : c_small_list_size };
            big_lists_count = big_lists_count > 0 ? big_lists_count - 1 : 0;

            auto dummy{ head };
            out.push_back(dummy);

            while (current_size > 1 && dummy && dummy->next)
            {
                current_size--;
                dummy = dummy->next;
            }

            if (dummy)
            {
                head = dummy->next;
                dummy->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
        }

        return out;
    }

private:
    std::size_t getListSize(ListNode* head)
    {
        std::size_t half_size{ 0 };
        auto slow{ head };
        auto fast{ head };

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            half_size++;
        }

        return fast ? half_size * 2 + 1 : half_size * 2;
    }
};

TEST(Leetcode_0725_split_linked_list_in_parts, test01)
{
    // Test it on https://leetcode.com/problems/split-linked-list-in-parts/... :)
}
