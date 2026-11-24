#include <vector>
#include "testing.hpp"

class Solution
{
public:
    // Explanation: Do non-decreasing merge in nums1 starting from the back
    void merge(std::vector<int>& nums1, int const size1, std::vector<int>& nums2, int const size2)
    {
        int it1{size1 - 1};
        int it2{size2 - 1};
        int final_it{size1 + size2 - 1};

        while (it1 >= 0 && it2 >= 0)
        {
            if (nums1[it1] >= nums2[it2])
            {
                nums1[final_it] = nums1[it1--];
            }
            else
            {
                nums1[final_it] = nums2[it2--];
            }
            --final_it;
        }

        while (it2 >= 0)
        {
            nums1[final_it--] = nums2[it2--];
        }
    }
};

//
// Explanation: Do non-decreasing merge in nums1 starting from the back
// Extended example
//
// [1,3,5,7,0,0,0,0,0,0,0]
// [1,2,3,4,5,6,7]
//
// [1,3,5,-,0,0,0,0,0,0,7]
// [1,2,3,4,5,6,7]
//
// [1,3,5,-,0,0,0,0,0,7,7]
// [1,2,3,4,5,6,-]
//
// [1,3,5,-,0,0,0,0,6,7,7]
// [1,2,3,4,5,-,-]
//
// [1,3,-,-,0,0,0,5,6,7,7]
// [1,2,3,4,5,-,-]
//
// [1,3,-,-,0,0,5,5,6,7,7]
// [1,2,3,4,5,-,-]
//
// [1,3,-,-,0,0,5,5,6,7,7]
// [1,2,3,4,-,-,-]
//
// [1,3,-,-,0,4,5,5,6,7,7]
// [1,2,3,-,-,-,-]
//
// [1,-,-,-,3,4,5,5,6,7,7]
// [1,2,3,-,-,-,-]
//
// [1,-,-,3,3,4,5,5,6,7,7]
// [1,2,-,-,-,-,-]
//
// [1,-,2,3,3,4,5,5,6,7,7]
// [1,-,-,-,-,-,-]
//
// [-,1,2,3,3,4,5,5,6,7,7]
// [1,-,-,-,-,-,-]
//
// [1,1,2,3,3,4,5,5,6,7,7]
// [-,-,-,-,-,-,-]
//

int main()
{
    {
        std::println("Example 1");
        auto nums1 = std::vector{1, 2, 3, 0, 0, 0};
        auto nums2 = std::vector{2, 5, 6};
        auto expected = std::vector{1, 2, 2, 3, 5, 6};
        Solution{}.merge(nums1, 3, nums2, 3);
        EXPECT_EQ(nums1, expected);
    }
    {
        std::println("Example 2");
        auto nums1 = std::vector{1};
        auto nums2 = std::vector<int>{};
        auto expected = std::vector{1};
        Solution{}.merge(nums1, 1, nums2, 0);
        EXPECT_EQ(nums1, expected);
    }
    {
        std::println("Example 2");
        auto nums1 = std::vector{0};
        auto nums2 = std::vector{1};
        auto expected = std::vector{1};
        Solution{}.merge(nums1, 0, nums2, 1);
        EXPECT_EQ(nums1, expected);
    }
    {
        std::println("Example 4");
        auto nums1 = std::vector{1, 3, 5, 7, 0, 0, 0, 0, 0, 0, 0};
        auto nums2 = std::vector{1, 2, 3, 4, 5, 6, 7};
        auto expected = std::vector{1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7};
        Solution{}.merge(nums1, 4, nums2, 7);
        EXPECT_EQ(nums1, expected);
    }
    {
        std::println("Example 5");
        auto nums1 = std::vector{1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0};
        auto nums2 = std::vector{1, 3, 5, 7};
        auto expected = std::vector{1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 7};
        Solution{}.merge(nums1, 7, nums2, 4);
        EXPECT_EQ(nums1, expected);
    }

    return 0;
}
