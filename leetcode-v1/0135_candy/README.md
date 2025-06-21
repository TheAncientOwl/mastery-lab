<h2>135. Candy ~ Hard</h2>

#### https://leetcode.com/problems/candy/

<p>There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.</p>

<p>You are giving candies to these children subjected to the following requirements:</p>

<ul>
	<li>Each child must have at least one candy.</li>
	<li>Children with a higher rating get more candies than their neighbors.</li>
</ul>

<p>Return <em>the minimum number of candies you need to have to distribute the candies to the children</em>.</p>


<h3>Example 1:</h3>

```
Input: ratings = [1,0,2]
Output: 5
Explanation You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
```

<h3>Example 2:</h3>

```
Input: ratings = [1,2,2]
Output: 4
Explanation You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
```


<h3>Constraints:</h3>

<ul>
	<li>n == ratings.length</li>
	<li>1 &lt;= n &lt;= 2 * 10<sup>4</sup></li>
	<li>0 &lt;= ratings[i] &lt;= 2 * 10<sup>4</sup></li>
</ul>

