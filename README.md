


# Algorithms_Codes

# Outline

&nbsp;&nbsp;This repository contains the source codes about implementation of some algorithms or data structurses that I need to know to study something about an algorithm. The source codes are written by me, referencing the original paper sugesting the source codes or some papers referencing the original paper.

## Contents

<table>
  <tr>
    <td > </td>
    <td><center><b>Category</b></center></td>
    <td><center><b>Name</b></center></td>
  </tr>
  <tr>
    <td rowspan= 2><center>Algorithms</center> </td>
    <td><center>Pattern Matching</center></td>
    <td><center><a href = "#AC_Automata">Aho-Corasick Automata</a></center></td>
  </tr>
  <tr>
    <td><center>2D Pattern Matching</center></td>
    <td><center><a href = "#BIRD_2D">BIRD Algorithm</a></center></td>
  </tr>
  <tr>
	  <td rowspan= 4><center>Data Structure</center></td>
	  <td><center>Binary Search Tree</center></td>
	  <td><center><a href = "#RB_TREE">Red-Black Tree</a></center></td>
  </tr>
  <tr>
	  <td><center>Priority_Queue</center></td>
	  <td><center><a href = "#Heap">Heap</a></center></td>
  </tr>
    <tr>
	  <td><center>Set</center></td>
	  <td><center><a href = "#DisjointSet">DisjointSet</a></center></td>
  </tr>
  <tr>
	  <td><center>Graph</center></td>
	  <td><center><a href = "#Graph_AdjacencyList">Adjacency List representation</a></center></td>
  </tr>
</table>

# Algorithms
&nbsp;&nbsp;Implementations of Algorithms using C++.
## Pattern Matching
&nbsp;&nbsp;Pattern matching problem is the problem that finds multiple or single pattern in multiple of single given text.

<p id = "AC_Automata"></p>

1. [Aho-Corasick Automata](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/01_Pattern_Matching/01_Aho-Corasick_Automata)
	> - Contributor: unsik6
	> - Reference: Alfred V. Aho and Margaret J. Corasick, "Efficient String Matching: An Aid to Bibliographic Search", ACM(1975) 18 (6) 333-340
	> - Language used to implement: C++
	> - Abstract:<br/>&nbsp;&nbsp; Aho-Corasck Automata is the deterministic automata to find all location of multiple patterns in a given text. Preprocessing patterns constructs the automata looked like a trie. Next, put a given text, the string in which we want to find patterns, in the automata.
	> - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; preprocessing by all patterns to construct the automata, including the trie, failure func and output func, needs time linear to sum the length of all patterns. And, Searching patterns in a given text needs time linear to the length of the text. If the sum of the length of all patterns is <i>m</i>, the alphabet used in the text is constant, and the length of the text is <i>n</i>, then the time complexity of this algorithm is $$O(m  + n)$$
	> - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; The number of nodes and edges of the automata is at most the sum of the length of patterns. And, the failure function can be stored as a linear array. If the patterns consist of only one character and their length are differnet from each other, the output function returns all patterns whose length is shorter than the new pattern founded. $$O(m^2)$$


<br/><br/>

## 2D Pattern Matching

<p id = "BIRD_2D"></p>

1. [BIRD Algorithm](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/02_2D_Pattern_Matching/01_BIRD_2D_Pattern_Matching)
 > - Contributor: unsik6
 > - Reference: R.S.Bird, "TWO DIMENSIONAL PATTERN MATCHING", IPL(1977), 168-170
 > - Language used to implement: C++
 > - Abstract: Two dimensional pattern matching algorithm of R. S. Bird uses Aho-Corasick automata and KMP pattern Matching algorithm. The rows of pattern(<i>m X m </i>) is considered multiple patterns. So, as Aho-Corasick automata is applied to row matching, Bird algorithm finds all rows that occur in a position of text(<i>n X n</i>). In two dimensional pattern matching, It can be siad that the patterns was found by finding all the rows of pattern in order. It can be computation using KMP algorithm.
 > - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; One of preprocessing to construct an AC automata by all rows of pattern needs <i>O(m<sup>2</sup>)</i> time. In the original paper, Other preprocessing, labeling all rows of pattern, was introduced it needs same time. but it can run in <i>O(m)</i> time using an AC automata already constructed. Also, It can run in the preprocessing to construct Output Func of an AC automata. The rest of preprocessing is to construct a KMP failure function using the labels of rows of pattern, and It runs in time in <i>O(m<sup>2</sup>)</i>.<br/>&nbsp;&nbsp;The prcessing to find all location of pattern in text run in  <i>O(n<sup>2</sup>)</i> time, since there are <i>n</i> column and KMP algorithm in each column needs <i>O(n)</i> time. And row matching needs <i>O(n<sup>2</sup>)</i> time, since Time complexity of the pattern matching using AC automata is linear. So, $$O(m^2 + m + m^2 + n^2 + n^2)$$ $$Total\ running\ time=O(n^2+m^2)$$
 > - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; There are an AC automata, which haves at most <i>m<sup>2</sup></i> nodes, the failure function of the AC automata that also have the same number of elements becuase it is implemented as array, the output function, which have <i>m<sup>2</sup></i> elements, and the KMP failure function, in column matching process, that have <i>m</i> elements. And we need the array that have <i>n</i> elements, to keep how many rows of pattern matched before using KMP algorithm in column matching. So, the space complexity of this algorithm is $$O(n+m^2)$$
<br/>


# Data Structures
## Binary Search Tree

<p id = "RB_TREE"></p>

1. [Red-Black Tree](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/01_Binary_Search_Tree/01_Red_Black_Tree)
 > - Contributor: unsik6
 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
 > - Language used to implement: C++
 > - Abstract:<br/>&nbsp;&nbsp; Red-Black Tree is one of the balenced binary search tree. Since the height of this tree is <i>O(log n)</i> when <i>n</i> is the number of the node that has a key, The queries including 'search', 'predecessor', 'successor', 'minimum(maximum)', 'insert' and 'delete' can run in <i>O(h) = O(log n)</i> time. The height of a general binary search tree is <i>O(n)</i>. Moreover, Red-Black Tree is more efficeint than AVL Tree, also one of the balenced binary search tree. In AVL Tree, the process to satisfy the balanced property in the insertion of deletion runs recursively in units of one level. But, The process, which has the same purpose, of Red-Black Tree runs recursively in units of two levels. <br/>&nbsp;&nbsp;There is Red-Black Tree class implemented using template in the "RB_Tree.h" of this repository. The node of the class has an element variable declared using template. And when a node is deleted, My Red-Black Tree uses the successor of the node which will be deleted. However,you can use the predecessor of the node that will be deleted like the pseucode of CLRS. And, you can see how Red-Black Tree works in [here](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)(using predecessor)!
 > - Time complexity: <br/>&nbsp;&nbsp;All queries can run in <i>O(h) = O(log n)</i> time. $$The\ time\ complexity\ of\ all\ queries=O(log n)$$
 > - Space complexity: <br/>&nbsp;&nbsp;All leaves of Red-Black Tree is NIL. I implements all NIL distinctly, but they can be implemented as an integrated NIL since all operation of Red-Black Tree don't call or reference the member of NIL. $$O(n)$$


<br/><br/>

## Priority Queue


<p id = "Heap"></p>

1. [Heap](https://github.com/unsik6/Algorithms_Codes/blob/main/02_Data_Structures/02_Priority_Queue/01_Heap/Heap.h)
> - Contributor: unsik6
 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
 > - Language used to implement: C++
 > - Abstract:<br/>&nbsp;&nbsp; Heap is the one of the famous data structure. Heap is the left-complete binary tree. The main property of heap is <i>par.key() <= children.key(), where the heap is Min-Heap</i>, If the heap is Max-Heap, the property is reversed. It is outstanding to implement Priority queue. Heap keeps the optimal value(minimum or maximum) at the root of heap. Since, the time complexity of <i>insert</i> and <i>removeOptimalValue(with getOptimalValue)</i> is <i>O(log n)</i>, where <i>n</i> is the number of elements, heap is used to sort in <i>O(nlog n) time</i>.
 > - Time complexity: <br/>&nbsp;&nbsp;$$Build\ Heap\ =O(n)$$ &nbsp;&nbsp;Since heap is the left-complete binary tree, the height of heap is <i>O(log n)</i>. So, $$Insert\ and\ removeOptimalValue =O(log n)$$
 > - Space complexity: (implementation: array)<br/>&nbsp;&nbsp; Since heap is the left-complete binary tree, heap don't need empty space, altough the heap is implemented as array. So, $$O(n)$$

<br/><br/>

## Set

<p id = "DisjointSet"></p>

1. [DisjointSet](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/03_Set/01_Disjoint_Set)
> - Contributor: unsik6
 > - Reference: [TECHIE DELIGT</>](https://www.techiedelight.com/ko/disjoint-set-data-structure-union-find-algorithm/)
 > - Language used to implement: C++
 > - Abstract:<br/>&nbsp;&nbsp; Disjoint Set(Union-Find Set) is a data structure implemented as a forest. Disjoint Set has sets that have the representative number. So, as I did, Disjoint Set can be implemented using the unordered_map<key, representative number of the set to which the key belongs>. Disjoint Set has two main operation, <i>Find</i> and <i>Union</i>. <i>Find</i> is passed a key and returns the representative of the set to wich the key belongs. <i>Union</i> is passed two keys. If the keys belong to the same set, it merges the sets.
 > - Time complexity: <br/>&nbsp;&nbsp; The time complexity of <i>Find</i> and <i>Union</i> is <i>O(n)</i>, if implemented as naive algorithm, where <i>n</i> is the number of elements. But, using <i>Path compression</i> and <i>Union by rank</i>, the time complexity is <i>amortized O(1)</i>. So, $$Find\ and\ Union =O(log n)$$
 > - Space complexity: (implementation: unorodered_set)<br/>&nbsp;&nbsp; It just need the pair, key and representative, by each elements. And, if appling <i>Path compression</i> and <i> Union by rank</i>, we need the pair, <representativ, height of the tree representing the set> by each set. The number of sets is less than the number of elements. So, $$O(n)$$


## Graph
<p id = "Graph_AdjacencyList"></p>

1. [Adjacency List representation](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList)
> - Contributor: unsik6
 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
 > - Language used to implement: C++
 > - Abstract:<br/>&nbsp;&nbsp; Adjacency List is the one of the representations of graph. The idea of this representation is storing the edges from each vector in same linked list. This representation needs less space than <i>Adjacency Matrix representation</i>.<br/>&nbsp;&nbsp; I implement that <i>std::vector<std::list<Edge*>*></i>. <i>Edge</i> is the custom class that has the pointers pointing the source vertex and the destination vertex and a weight. I implement Adjacency List as template class that need two type defined by user. The first type is the type of the element of vertices and the second type is the type of the weight of edges.
 > - Time complexity: !!! This time complexity is not about Adjacency List ADT. !!!<br/>&nbsp;&nbsp; <i>Insert vertex</i> needs that the two array is inserted each one element, so the operation runs in <i>amortized O(1)</i> time. <i>delete vertex</i> and <i>find vertex</i> by the element of vertex runs in <i>O(|V|)</i>, where <i>V</i> is the set of vertices. The operations need to find the vertex having the element we input.  <i>insert edge</i> by a weight and two elements of vertices, source vertex and destination vertex, runs in <i>O(|V|)</i> time. The operation need to find the index of  the source vertex. <i>delete edge</i> by the same parameters runs in <i>O(|V|+|E|)</i> time, where <i>E</i> is the set of edges. The operation need to visit adjacency lists of all vertices and edges. <i>find edge</i> by the same parameters runs in <i>O(degree of source vertex)</i>.
 > - Space complexity: !!! This time complexity is not about Adjacency List ADT. !!!<br/>&nbsp;&nbsp; I added one more array(<i>std::vector<Vertex*></i>) having pointers of all vertices. This array needs <i>O(|V|)</i> space. Adjacency lists of all vertices have pointers of all edges. And all adjacency lists are stored in same array. So, we need <i>O(|V| + |E|)</i> space. Since we don't discuss about the number of elements of vertex and edge, total space complexity is <i>O(|V| + |E|)</i>.

<br/>
