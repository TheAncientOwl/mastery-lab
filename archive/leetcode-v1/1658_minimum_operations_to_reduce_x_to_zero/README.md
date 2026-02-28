<h2>1658. Minimum Operations to Reduce X to Zero ~ Medium</h2>

#### https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/

<p>You are given an integer array <code>nums</code> and an integer <code>x</code>. In one operation, you can either remove the leftmost or the rightmost element from the array <code>nums</code> and subtract its value from <code>x</code>. Note that this <strong>modifies</strong> the array for future operations.</p>

<p>Return <em>the <strong>minimum number</strong> of operations to reduce </em><code>x</code> <em>to <strong>exactly</strong></em> <code>0</code> <em>if it is possible</em><em>, otherwise, return </em><code>-1</code>.</p>


<h3>Example 1:</h3>

<pre>
<code>Input: nums = [1,1,4,2,3], x = 5
Output: 2
Explanation The optimal solution is to remove the last two elements to reduce x to zero.
</code></pre>

<h3>Example 2:</h3>

<pre>
<code>Input: nums = [5,6,7,8,9], x = 4
Output: -1
</code></pre>

<h3>Example 3:</h3>

<pre>
<code>Input: nums = [3,2,20,1,1,3], x = 10
Output: 5
Explanation The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
</code></pre>


<h3>Constraints:</h3>

<ul>
	<li><code>1 &lt;= nums.length &lt;= 10<sup>5</sup></code></li>
	<li><code>1 &lt;= nums[i] &lt;= 10<sup>4</sup></code></li>
	<li><code>1 &lt;= x &lt;= 10<sup>9</sup></code></li>
</ul>

