<h2>332. Reconstruct Itinerary ~ Hard</h2>

#### https://leetcode.com/problems/reconstruct-itinerary/

<p>You are given a list of airline tickets where tickets[i] = [from<sub>i</sub>, to<sub>i</sub>] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.</p>

<p>All of the tickets belong to a man who departs from JFK, thus, the itinerary must begin with JFK. If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.</p>

<ul>
	<li>For example, the itinerary [JFK, LGA] has a smaller lexical order than [JFK, LGB].</li>
</ul>

<p>You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.</p>


<h3>Example 1:</h3>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/14/itinerary1-graph.jpg" style="width: 382px; height: 222px;" />

```
Input: tickets = [[MUC,LHR],[JFK,MUC],[SFO,SJC],[LHR,SFO]]
Output: [JFK,MUC,LHR,SFO,SJC]
```

<h3>Example 2:</h3>
<img alt="" src="https://assets.leetcode.com/uploads/2021/03/14/itinerary2-graph.jpg" style="width: 222px; height: 230px;" />

```
Input: tickets = [[JFK,SFO],[JFK,ATL],[SFO,ATL],[ATL,JFK],[ATL,SFO]]
Output: [JFK,ATL,JFK,SFO,ATL,SFO]
Explanation Another possible reconstruction is [JFK,SFO,ATL,JFK,ATL,SFO] but it is larger in lexical order.
```


<h3>Constraints:</h3>

<ul>
	<li>1 &lt;= tickets.length &lt;= 300</li>
	<li>tickets[i].length == 2</li>
	<li>from<sub>i</sub>.length == 3</li>
	<li>to<sub>i</sub>.length == 3</li>
	<li>from<sub>i</sub> and to<sub>i</sub> consist of uppercase English letters.</li>
	<li>from<sub>i</sub> != to<sub>i</sub></li>
</ul>

