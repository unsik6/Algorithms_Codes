
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


1. [Aho-Corasick Automata](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/01_Pattern_Matching/01_Aho-Corasick_Automata)

>  - Contributor: unsik6
>  - Reference: Alfred V. Aho and Margaret J. Corasick, "Efficient String Matching: An Aid to Bibliographic Search", ACM(1975) 18 (6) 333-340
>  - Language used to implement: C++
>  - Abstract:<br/>&nbsp;&nbsp; Aho-Corasck Automata is the deterministic automata to find all location of multiple patterns in a given text. Preprocessing patterns constructs the automata looked like a trie. Next, put a give text, the string in which we want to find patterns, in the automata.
>  - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; preprocessing by all patterns to construct the automata, including the trie, failure func and output func, needs time linear to sum the length of all patterns. And, Searching patterns in a given text needs time linear to the length of the text. If the sum of the length of all patterns is <i>m</i>, the alphabet used in the text is constant, and the length of the text is <i>n</i>, then the time complexity of this algorithm is $$O(m + n)$$
>  - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; The number of nodes and edges of the automata is at most the sum of the length of patterns. And, the failure function can be stored as a linear array. If the patterns consist of only one character and their length are differnet from each other, the output function returns all patterns whose length is shorter than the new pattern founded. $$O(m^2)$$
<br/>


# Data Structure
## Binary Search Tree
1. [Red-Black Tree](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/01_Binary_Search_Tree/01_Red_Black_Tree)
 > - Contributor: unsik6
 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
 > - Language used to implement: C++
 > - Abstract:<br/>&nbsp;&nbsp; Red-Black Tree is one of the balenced binary search tree. Since the height of this tree is <i>O(log n)</i> when <i>n</i> is the number of the node that has a key, The queries including 'search', 'predecessor', 'successor', 'minimum(maximum)', 'insert' and 'delete' can run in <i>O(h) = O(log n)</i> time. The height of a general binary search tree is <i>O(n)</i>. Moreover, Red-Black Tree is more efficeint than AVL Tree, also one of the balenced binary search tree. In AVL Tree, the process to satisfy the balanced property in the insertion of deletion runs recursively in units of one level. But, The process, which has the same purpose, of Red-Black Tree runs recursively in units of two levels. <br/>&nbsp;&nbsp;There is Red-Black Tree class implemented using template in the "RB_Tree.h" of this repository. The node of the class has an element variable declared using template. And when a node is deleted, My Red-Black Tree uses the successor of the node which will be deleted. However,you can use the predecessor of the node that will be deleted like the pseucode of CLRS. And, you can see how Red-Black Tree works in [here](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)(using predecessor)!
 > - Time complexity: <br/>&nbsp;&nbsp;All queries can run in <i>O(h) = O(log n)</i> time. $$The\ time\ complexity\ of\ all\ queries=O(log n)$$
 > - Space complexity: <br/>&nbsp;&nbsp;All leaves of Red-Black Tree is NIL. I implements all NIL distinctly, but they can be implemented as an integrated NIL since all operation of Red-Black Tree don't call or reference the member of NIL. $$O(n)$$
<br/>
