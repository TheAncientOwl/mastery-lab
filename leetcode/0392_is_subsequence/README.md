<h2>392. Is Subsequence ~ Easy</h2>

#### https://leetcode.com/problems/is-subsequence/

<p>Given two strings <code>s</code> and <code>t</code>, return <code>true</code><em> if </em><code>s</code><em> is a <strong>subsequence</strong> of </em><code>t</code><em>, or </em><code>false</code><em> otherwise</em>.</p>

<p>A <strong>subsequence</strong> of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., <code>ace</code> is a subsequence of <code><u>a</u>b<u>c</u>d<u>e</u></code> while <code>aec</code> is not).</p>


<h3>Example 1:</h3>
<pre><code>Input: s = "abc", t = "ahbgdc"
Output: true
</code></pre><h3>Example 2:</h3>
<pre><code>Input: s = "axc", t = "ahbgdc"
Output: false
</code></pre>

<h3>Constraints:</h3>

<ul>
	<li><code>0 &lt;= s.length &lt;= 100</code></li>
	<li><code>0 &lt;= t.length &lt;= 10<sup>4</sup></code></li>
	<li><code>s</code> and <code>t</code> consist only of lowercase English letters.</li>
</ul>


<strong>Follow up:</strong> Suppose there are lots of incoming <code>s</code>, say <code>s<sub>1</sub>, s<sub>2</sub>, ..., s<sub>k</sub></code> where <code>k &gt;= 10<sup>9</sup></code>, and you want to check one by one to see if <code>t</code> has its subsequence. In this scenario, how would you change your code?
