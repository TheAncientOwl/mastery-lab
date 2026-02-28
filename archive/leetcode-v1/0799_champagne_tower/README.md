<h2>799. Champagne Tower ~ Medium</h2>

#### https://leetcode.com/problems/champagne-tower/

<p>We stack glasses in a pyramid, where the <strong>first</strong> row has <code>1</code> glass, the <strong>second</strong> row has <code>2</code> glasses, and so on until the 100<sup>th</sup> row.&nbsp; Each glass holds one cup&nbsp;of champagne.</p>

<p>Then, some champagne is poured into the first glass at the top.&nbsp; When the topmost glass is full, any excess liquid poured will fall equally to the glass immediately to the left and right of it.&nbsp; When those glasses become full, any excess champagne will fall equally to the left and right of those glasses, and so on.&nbsp; (A glass at the bottom row has its excess champagne fall on the floor.)</p>

<p>For example, after one cup of champagne is poured, the top most glass is full.&nbsp; After two cups of champagne are poured, the two glasses on the second row are half full.&nbsp; After three cups of champagne are poured, those two cups become full - there are 3 full glasses total now.&nbsp; After four cups of champagne are poured, the third row has the middle glass half full, and the two outside glasses are a quarter full, as pictured below.</p>

<p><img alt="" src="https://s3-lc-upload.s3.amazonaws.com/uploads/2018/03/09/tower.png" style="height: 241px; width: 350px;" /></p>

<p>Now after pouring some non-negative integer cups of champagne, return how full the <code>j<sup>th</sup></code> glass in the <code>i<sup>th</sup></code> row is (both <code>i</code> and <code>j</code> are 0-indexed.)</p>


<h3>Example 1:</h3>

<pre>
<code>Input: poured = 1, query_row = 1, query_glass = 1
Output: 0.00000
Explanation We poured 1 cup of champange to the top glass of the tower (which is indexed as (0, 0)). There will be no excess liquid so all the glasses under the top glass will remain empty.
</code></pre>

<h3>Example 2:</h3>

<pre>
<code>Input: poured = 2, query_row = 1, query_glass = 1
Output: 0.50000
Explanation We poured 2 cups of champange to the top glass of the tower (which is indexed as (0, 0)). There is one cup of excess liquid. The glass indexed as (1, 0) and the glass indexed as (1, 1) will share the excess liquid equally, and each will get half cup of champange.
</code></pre>

<h3>Example 3:</h3>

<pre>
<code>Input: poured = 100000009, query_row = 33, query_glass = 17
Output: 1.00000
</code></pre>


<h3>Constraints:</h3>

<ul>
	<li><code>0 &lt;=&nbsp;poured &lt;= 10<sup>9</sup></code></li>
	<li><code>0 &lt;= query_glass &lt;= query_row&nbsp;&lt; 100</code></li>
</ul>
