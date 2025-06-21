<h2>1359. Count All Valid Pickup and Delivery Options ~ Hard</h2>

#### https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

<p>Given <code>n</code> orders, each order consist in pickup and delivery services.&nbsp;</p>

<p>Count all valid pickup/delivery possible sequences such that delivery(i) is always after of&nbsp;pickup(i).&nbsp;</p>

<p>Since the answer&nbsp;may be too large,&nbsp;return it modulo&nbsp;10^9 + 7.</p>


<h3>Example 1:</h3>

```
Input: n = 1
Output: 1
Explanation Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
```

<h3>Example 2:</h3>

```
Input: n = 2
Output: 6
Explanation All possible orders: 
(P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
This is an invalid order (P1,D2,P2,D1) because Pickup 2 is after of Delivery 2.
```

<h3>Example 3:</h3>

```
Input: n = 3
Output: 90
```


<h3>Constraints:</h3>

<ul>
	<li><code>1 &lt;= n &lt;= 500</code></li>
</ul>

