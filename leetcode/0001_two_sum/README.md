<h2>1. Two Sum ~ Easy</h2>

#### https://leetcode.com/problems/two-sum/

<p>Given an array of integers <code>nums</code>&nbsp;and an integer <code>target</code>, return <em>indices of the two numbers such that they add up to <code>target</code></em>.</p>

<p>You may assume that each input would have <strong><em>exactly</em> one solution</strong>, and you may not use the <em>same</em> element twice.</p>

<p>You can return the answer in any order.</p>


<h3>Example 1:</h3>

```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation Because nums[0] + nums[1] == 9, we return [0, 1].
```

<h3>Example 2:</h3>

```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

<h3>Example 3:</h3>

```
Input: nums = [3,3], target = 6
Output: [0,1]
```


<h3>Constraints:</h3>

<ul>
	<li><code>2 &lt;= nums.length &lt;= 10<sup>4</sup></code></li>
	<li><code>-10<sup>9</sup> &lt;= nums[i] &lt;= 10<sup>9</sup></code></li>
	<li><code>-10<sup>9</sup> &lt;= target &lt;= 10<sup>9</sup></code></li>
	<li><strong>Only one valid answer exists.</strong></li>
</ul>


<strong>Follow-up:&nbsp;</strong>Can you come up with an algorithm that is less than <code>O(n<sup>2</sup>)</code><font face="monospace">&nbsp;</font>time complexity?
