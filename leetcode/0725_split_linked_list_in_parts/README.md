<h2>725. Split Linked List in Parts ~ Medium</h2>

#### https://leetcode.com/problems/split-linked-list-in-parts/

<p>Given the <code>head</code> of a singly linked list and an integer <code>k</code>, split the linked list into <code>k</code> consecutive linked list parts.</p>

<p>The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.</p>

<p>The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.</p>

<p>Return <em>an array of the </em><code>k</code><em> parts</em>.</p>


<h3>Example 1:</h3>
<img alt="" src="https://assets.leetcode.com/uploads/2021/06/13/split1-lc.jpg" style="width: 400px; height: 134px;" />

```
Input: head = [1,2,3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but its string representation as a ListNode is [].
```

<h3>Example 2:</h3>
<img alt="" src="https://assets.leetcode.com/uploads/2021/06/13/split2-lc.jpg" style="width: 600px; height: 60px;" />

```
Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
Output: [[1,2,3,4],[5,6,7],[8,9,10]]
Explanation
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
```


<h3>Constraints:</h3>

<ul>
	<li>The number of nodes in the list is in the range <code>[0, 1000]</code>.</li>
	<li><code>0 &lt;= Node.val &lt;= 1000</code></li>
	<li><code>1 &lt;= k &lt;= 50</code></li>
</ul>

