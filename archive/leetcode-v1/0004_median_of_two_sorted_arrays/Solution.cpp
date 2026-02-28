#include <gtest/gtest.h>

#include <vector>

class Solution
{
public:
    double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const auto c_total_size{ nums1.size() + nums2.size() };
        const auto c_middle_pos{
            c_total_size % 2 == 0
            ? static_cast<std::size_t>((c_total_size - 1) / 2)
            : static_cast<std::size_t>(c_total_size / 2)
        };

        auto i1{ 0ul };
        auto i2{ 0ul };
        double out{ 0.0 };

        for (auto i = 0; i <= c_middle_pos; i++)
        {
            out = getMin(nums1, i1, nums2, i2);
        }

        if (c_total_size % 2 == 0)
        {
            out += getMin(nums1, i1, nums2, i2);
            out /= 2.0;
        }

        return out;
    }

private:
    int getMin(const std::vector<int>& nums1, std::size_t& i1, const std::vector<int>& nums2, std::size_t& i2)
    {
        if (i1 < nums1.size() && i2 < nums2.size())
        {
            return nums1[i1] < nums2[i2] ? nums1[i1++] : nums2[i2++];
        }
        else if (i1 < nums1.size())
        {
            return nums1[i1++];
        }
        else if (i2 < nums2.size())
        {
            return nums2[i2++];
        }

        return -1;
    }
};

TEST(Leetcode_0004_median_of_two_sorted_arrays, test01)
{
    const std::vector<int> in1{ 1, 3 };
    const std::vector<int> in2{ 2 };
    const auto expected{ 2.0 };
    const auto out{ Solution{}.findMedianSortedArrays(in1, in2) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0004_median_of_two_sorted_arrays, test02)
{
    const std::vector<int> in1{ 1, 2 };
    const std::vector<int> in2{ 3, 4 };
    const auto expected{ 2.5 };
    const auto out{ Solution{}.findMedianSortedArrays(in1, in2) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0004_median_of_two_sorted_arrays, test03)
{
    const std::vector<int> in1{ 1, 3, 5, 7, 9 };
    const std::vector<int> in2{ 2, 4, 6, 8 };
    const auto expected{ 5.0 };
    const auto out{ Solution{}.findMedianSortedArrays(in1, in2) };

    EXPECT_EQ(out, expected);
}

TEST(Leetcode_0004_median_of_two_sorted_arrays, test04)
{
    const std::vector<int> in1{ 1, 3, 5, 7, 9 };
    const std::vector<int> in2{ 2, 4, 6, 8, 10 };
    const auto expected{ 5.5 };
    const auto out{ Solution{}.findMedianSortedArrays(in1, in2) };

    EXPECT_EQ(out, expected);
}
