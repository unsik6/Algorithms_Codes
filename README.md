
# Algorithms_Codes

# Outline

&nbsp;&nbsp;This repository contains the source codes about implementation of some algorithms or data structurses that I need to know to study something about an algorithm. The source codes are written by me, referencing the original paper sugesting the source codes ore some papers referencing the original paper.

# Algorithms
&nbsp;&nbsp;Implementations of Algorithms using C++.
## Pattern Matching
&nbsp;&nbsp;Pattern matching problem is the problem that finds multiple or single pattern in multiple of single given text.
1. [Aho-Corasick Automata](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/01_Pattern_Matching/01_Aho-Corasick_Automata)
	> - Contributor: unsik6
	> - Reference: Alfred V. Aho and Margaret J. Corasick, "Efficient String Matching: An Aid to Bibliographic Search", ACM(1975) 18 (6) 333-340
	> - Language used to implement: C++
	> - Abstract:<br/>&nbsp;&nbsp; Aho-Corasck Automata is the deterministic automata to find all location of multiple patterns in a given text. Preprocessing patterns constructs the automata looked like a trie. Next, put a give text, the string in which we want to find patterns, in the automata.
	> - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; preprocessing by all patterns to construct the automata, including the trie, failure func and output func, needs time linear to sum the length of all patterns. And, Searching patterns in a given text needs time linear to the length of the text. If the sum of the length of all patterns is <i>m</i>, the alphabet used in the text is constant, and the length of the text is <i>n</i>, then the time complexity of this algorithm is $$O(m  + n)$$
	> - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; The number of nodes and edges of the automata is at most the sum of the length of patterns. And, the failure function can be stored as a linear array. If the patterns consist of only one character and their length are differnet from each other, the output function returns all patterns whose length is shorter than the new pattern founded. $$O(m^2)$$


<br/><br/>


## 2D Pattern Matching
1. [BIRD Algorithm](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/02_2D_Pattern_Matching/01_BIRD_2D_Pattern_Matching)
 > - Contributor: unsik6
 > - Reference: R.S.Bird, "TWO DIMENSIONAL PATTERN MATCHING", IPL(1977), 168-170
 > - Language used to implement: C++
 > - Abstract: Two dimensional pattern matching algorithm of R. S. Bird uses Aho-Corasick automata and KMP pattern Matching algorithm. The rows of pattern(<i>m X m </i>) is considered multiple patterns. So, as Aho-Corasick automata is applied to row matching, Bird algorithm finds all rows that occur in a position of text(<i>n X n</i>). In two dimensional pattern matching, It can be siad that the patterns was found by finding all the rows of pattern in order. It can be computation using KMP algorithm.
 > - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; One of preprocessing to construct an AC automata by all rows of pattern needs <i>O(m<sup>2</sup>)</i> time. In the original paper, Other preprocessing, labeling all rows of pattern, was introduced it needs same time. but it can run in <i>O(m)</i> time using an AC automata already constructed. Also, It can run in the preprocessing to construct Output Func of an AC automata. The rest of preprocessing is to construct a KMP failure function using the labels of rows of pattern, and It runs in time in <i>O(m<sup>2</sup>)</i>.<br/>&nbsp;&nbsp;The prcessing to find all location of pattern in text run in  <i>O(n<sup>2</sup>)</i> time, since there are <i>n</i> column and KMP algorithm in each column needs <i>O(n)</i> time. And row matching needs <i>O(n<sup>2</sup>)</i> time, since Time complexity of the pattern matching using AC automata is linear. So, $$O(m^2 + m + m^2 + n^2 + n^2)$$ $$Total\ running\ time=O(n^2+m^2)$$
 > - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; There are an AC automata, which haves at most <i>m<sup>2</sup></i> nodes, the failure function of the AC automata that also have the same number of elements becuase it is implemented as array, the output function, which have <i>m<sup>2</sup></i> elements, and the KMP failure function, in column matching process, that have <i>m</i> elements. And we need the array that have <i>n</i> elements, to keep how many rows of pattern matched before using KMP algorithm in column matching. So, the space complexity of this algorithm is $$O(n+m^2)$$
<br/>
