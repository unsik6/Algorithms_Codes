2. Rabin-Karp
	> - Contributor: StoneIron02
	> - Reference: CLRS 3E
	> - Language used to implement: C++
	> - Abstract:<br/>&nbsp;&nbsp; Rabin-Karp Algorithm is one of the pattern matching algorithms to find all locations of pattern in the given text. This algorithm separates text into substrings that have the length of the pattern and converts pattern and substrings into numbers. After that, compare each number by using modulo.<br/><br/>
	> - Time complexity: <br/>&nbsp;&nbsp; Let the the length of pattern is <i>m</i>, and the length of text is <i>n</i>. It takes <i>O(m)</i> time to preprocess the first substring of the pattern and text. It takes <i>O(n-m)</i> time to compute the number of the next substring. If each number of pattern and substring is the same, we should compare the original string to find valid shifts. That takes <i>O(m)¡¿O(the sum of valid shifts and spurious hits)</i>. So, worst case is $$O((n-m+1)m)$$ and expected time, if the number of valid shifts are <i>O(1)</i> and q is more than m, is $$O(n)$$
	> - Space complexity: <br/>&nbsp;&nbsp; Equals the sum of the length of pattern and text. $$O(n+m)$$
