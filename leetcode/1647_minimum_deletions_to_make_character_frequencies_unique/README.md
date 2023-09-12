<h2>1647. Minimum Deletions to Make Character Frequencies Unique ~ Medium</h2>

#### https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/

<p>A string s is called <strong>good</strong> if there are no two different characters in s that have the same <strong>frequency</strong>.</p>

<p>Given a string s, return<em> the <strong>minimum</strong> number of characters you need to delete to make </em>s<em> <strong>good</strong>.</em></p>

<p>The <strong>frequency</strong> of a character in a string is the number of times it appears in the string. For example, in the string aab, the <strong>frequency</strong> of &#39;a&#39; is 2, while the <strong>frequency</strong> of &#39;b&#39; is 1.</p>


<h3>Example 1:</h3>

```
Input: s = aab
Output: 0
Explanation s is already good.
```

<h3>Example 2:</h3>

```
Input: s = aaabbbcc
Output: 2
Explanation You can delete two &#39;b&#39;s resulting in the good string aaabcc.
Another way it to delete one &#39;b&#39; and one &#39;c&#39; resulting in the good string aaabbc.
```

<h3>Example 3:</h3>

```
Input: s = ceabaacb
Output: 2
Explanation You can delete both &#39;c&#39;s resulting in the good string eabaab.
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
```


<h3>Constraints:</h3>

<ul>
	<li>1 &lt;= s.length &lt;= 10<sup>5</sup></li>
	<li>s&nbsp;contains only lowercase English letters.</li>
</ul>

