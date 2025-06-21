<h2>4. Median of Two Sorted Arrays ~ Hard</h2>

#### https://leetcode.com/problems/median-of-two-sorted-arrays/

<p>Given two sorted arrays <code>nums1</code> and <code>nums2</code> of size <code>m</code> and <code>n</code> respectively, return <strong>the median</strong> of the two sorted arrays.</p>

<p>The overall run time complexity should be <code>O(log (m+n))</code>.</p>


<h3>Example 1:</h3>

<pre>
<code>Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation merged array = [1,2,3] and median is 2.
</code></pre>

<h3>Example 2:</h3>

<pre>
<code>Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
</code></pre>


<h3>Constraints:</h3>

<ul>
	<li><code>nums1.length == m</code></li>
	<li><code>nums2.length == n</code></li>
	<li><code>0 &lt;= m &lt;= 1000</code></li>
	<li><code>0 &lt;= n &lt;= 1000</code></li>
	<li><code>1 &lt;= m + n &lt;= 2000</code></li>
	<li><code>-10<sup>6</sup> &lt;= nums1[i], nums2[i] &lt;= 10<sup>6</sup></code></li>
</ul>

