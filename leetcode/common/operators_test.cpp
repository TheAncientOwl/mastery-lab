#include "testing.hpp" // IWYU pragma: keep

#include <sstream>
#include <utility>
#include <vector>

TEST(ContainerOperators, StreamsNestedContainers)
{
    auto const values = std::vector<std::vector<int>>{{1, 2}, {3, 4}};
    std::ostringstream output;

    output << values;

    EXPECT_EQ(output.str(), "[[1, 2], [3, 4]]");
}

TEST(ContainerOperators, StreamsPairs)
{
    auto const values = std::vector<std::pair<int, int>>{{1, 2}, {3, 4}};
    std::ostringstream output;

    output << values;

    EXPECT_EQ(output.str(), "[(1, 2), (3, 4)]");
}
