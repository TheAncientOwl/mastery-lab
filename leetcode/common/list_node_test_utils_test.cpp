#include "testing.hpp"

#include "ListNode.hpp"

TEST(ListNodeTestUtils, BuildsAndReadsLists)
{
    ListNodeTestUtils::Arena<ListNode> arena;
    auto* list = arena.make_list({1, 2, 3});

    EXPECT_EQ(arena.values(list), (std::vector<int>{1, 2, 3}));
}

TEST(ListNodeTestUtils, TracksNewNodesAndHandlesEmptyLists)
{
    ListNodeTestUtils::Arena<ListNode> arena;
    auto* list = arena.make_list({});
    ASSERT_EQ(list, nullptr);

    list = new ListNode{4};
    list->next = new ListNode{5};
    arena.track(list);

    EXPECT_EQ(arena.values(list), (std::vector<int>{4, 5}));
}
