






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
    <td rowspan= 5><center>Algorithms</center> </td>
    <td rowspan = 2><center>String Matching</center></td>
    <td><center><a href = "#AC_Automata">Aho-Corasick Automata</a></center></td>
  </tr>
  <tr>
	  <td><center><a href = "#Rabin_Karp">Rabin-Karp algorithm</a></center></td>
  </tr>
  <tr>
    <td><center>2D String Matching</center></td>
    <td><center><a href = "#BIRD_2D">BAKER-BIRD Algorithm</a></center></td>
  </tr>
  <tr>
    <td rowspan= 2><center>Graph Algorithms</center></td>
    <td><center><a href = "#MST">MST</a><br/>(<a href = "#Prim_Algorithm">Prim's Algorithm</a>, <a href = "#Kruskal_Algorithm">Kruskal's Algorithm</a>)</center></td>
  </tr>
  <tr>
	  <td><center><a href = "#ShortestPath">Shortest Path</a><br/>(<a href = "#Dijkstra">Dijkstra's Algorithm</a>, <a href = "#Bellman-Ford">Bellman-Ford's Algorithm</a>,<br/> <a href = "#Floyd-Warshall">Floyd-Warshall's Algorithm</a>)</center></td>
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
## Pattern Matching
- Pattern matching problem is the problem that finds multiple or single pattern in multiple of single given text.

<p id = "AC_Automata"></p>

1. [<b>Aho-Corasick Automata</b>](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/01_Pattern_Matching/01_Aho-Corasick_Automata)
	> - Contributor: unsik6
	> - Reference: Alfred V. Aho and Margaret J. Corasick, "Efficient String Matching: An Aid to Bibliographic Search", ACM(1975) 18 (6) 333-340
	> - Language used to implement: C++
	> - Abstract:<br/>&nbsp;&nbsp; Aho-Corasck Automata is the deterministic automata to find all location of multiple patterns in a given text. Preprocessing patterns constructs the automata looked like a trie. Next, put a given text, the string in which we want to find patterns, in the automata.<br/><br/>
	> - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; preprocessing by all patterns to construct the automata, including the trie, failure func and output func, needs time linear to sum the length of all patterns. And, Searching patterns in a given text needs time linear to the length of the text. If the sum of the length of all patterns is <i>m</i>, the alphabet used in the text is constant, and the length of the text is <i>n</i>, then the time complexity of this algorithm is $$O(m  + n)$$<br/>
	> - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; The number of nodes and edges of the automata is at most the sum of the length of patterns. And, the failure function can be stored as a linear array. If the patterns consist of only one character and their length are differnet from each other, the output function returns all patterns whose length is shorter than the new pattern founded. $$O(m^2)$$

<br/>

<p id = "Rabin_Karp"></p>

2. [<b>Rabin-Karp</b>](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/01_Pattern_Matching/02_Rabin-Karp)
	> - Contributor: StoneIron02
	> - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	> - Language used to implement: C++
	> - Abstract:<br/>&nbsp;&nbsp; Rabin-Karp Algorithm is one of the pattern matching algorithms to find all locations of pattern in the given text. This algorithm separates text into substrings that have the length of the pattern and converts pattern and substrings into numbers. After that, compare each number by using modulo.<br/><br/>
	> - Time complexity: <br/>&nbsp;&nbsp; Let the the length of pattern is <i>m</i>, and the length of text is <i>n</i>. It takes <i>O(m)</i> time to preprocess the first substring of the pattern and text. It takes <i>O(n-m)</i> time to compute the number of the next substring. If each number of pattern and substring is the same, we should compare the original string to find valid shifts. That takes <i>O(m)*O(the sum of valid shifts and spurious hits)</i>. So, worst case is $$O((n-m+1)m)$$ and expected time, if the number of valid shifts are <i>O(1)</i> and q is more than m, is $$O(n)$$<br/>
	> - Space complexity: <br/>&nbsp;&nbsp; Equals the sum of the length of pattern and text. $$O(n+m)$$
	
<br/><br/>

## 2D Pattern Matching

<p id = "BIRD_2D"></p>

1. [<b>BAKER-BIRD Algorithm</b>](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/02_2D_Pattern_Matching/01_BIRD_2D_Pattern_Matching)
	 > - Contributor: unsik6
	 > - Reference: R.S.Bird, "TWO DIMENSIONAL PATTERN MATCHING", IPL(1977), 168-170 & THEODORE P. BAKER, "A Technique for extending rapid exact-match string matching to arrays of more than one dimension", SIAM J. Comput. (1978), 533-541
	 > - Language used to implement: C++
	 > - Abstract: <br/>&nbsp;&nbsp;Two dimensional pattern matching algorithm of R. S. Bird uses Aho-Corasick automata and KMP pattern Matching algorithm. The rows of pattern(<i>m X m </i>) is considered multiple patterns. So, as Aho-Corasick automata is applied to row matching, Bird algorithm finds all rows that occur in a position of text(<i>n X n</i>). In two dimensional pattern matching, It can be siad that the patterns was found by finding all the rows of pattern in order. It can be computation using KMP algorithm.
	 > <br/>&nbsp;&nbsp; Baker also published a paper introducing two dimensional pattern matching. He use only M-P algorithm and it's automaton. He extended M-P automaton for row matching, but that is almost same with Aho-Corasick automaton. And in column matching, Baker use M-P automaton(M-P algorithm equals KMP). So, generally, Baker's algorithm and Bird's algorithm are combined and called 'Baker-Bird algorithm'.<br/><br/>
	 > - Time complexity: (implementation: array) <br/>&nbsp;&nbsp; One of preprocessing to construct an AC automata by all rows of pattern needs <i>O(m<sup>2</sup>)</i> time. In the original paper, Other preprocessing, labeling all rows of pattern, was introduced it needs same time. but it can run in <i>O(m)</i> time using an AC automata already constructed. Also, It can run in the preprocessing to construct Output Func of an AC automata. The rest of preprocessing is to construct a KMP failure function using the labels of rows of pattern, and It runs in time in <i>O(m<sup>2</sup>)</i>.<br/>&nbsp;&nbsp;The prcessing to find all location of pattern in text run in  <i>O(n<sup>2</sup>)</i> time, since there are <i>n</i> column and KMP algorithm in each column needs <i>O(n)</i> time. And row matching needs <i>O(n<sup>2</sup>)</i> time, since Time complexity of the pattern matching using AC automata is linear. So, $$O(m^2 + m + m^2 + n^2 + n^2)$$ $$Total\ running\ time=O(n^2+m^2)$$<br/>
	 > - Space complexity: (implementation: array) <br/>&nbsp;&nbsp; There are an AC automata, which haves at most <i>m<sup>2</sup></i> nodes, the failure function of the AC automata that also have the same number of elements becuase it is implemented as array, the output function, which have <i>m<sup>2</sup></i> elements, and the KMP failure function, in column matching process, that have <i>m</i> elements. And we need the array that have <i>n</i> elements, to keep how many rows of pattern matched before using KMP algorithm in column matching. So, the space complexity of this algorithm is $$O(n+m^2)$$
<br/><br/>

## Graph Algorithm

<p id = "MST"></p>

### [MST](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/03_Graph_algorithms/01_MST)

- Minimum Spanning Tree(MST) problem is one of the famous problems. The problem is finding a spanning tree with the minimum weight of a given connected, undirected graph. It is no matter the given graph is weighted or not. If the given graph is unweighted, we can solve the problem considering the weights of all edges are same. A spanning tree for a connected, undirected graph is an undirected tree, a subgraph which includes all vertices of the given graph. The weight of a spanning tree is the sum of the weight of all edges of itself. If a spanning tree has the least weight than othes, the spanning tree is MST.
- Here are two MST algorithms, Prim's and Kruskal's. The algorithms are implemented in one namespace <i>MST</i>,
- They return different datatype. So, If you want to test the algorithm, NOT use the function named the name of algorithms. please use the function whose name starts with <i>print</i>.

<p id = "Prim_Algorithm"></p>

1. <b> Prim's Algorithm</b>
	 > - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; <i>Prim's algorithm</i> is the algorithm to find MST. The idea of Prim's algorithm is like BFS. We insert the root vertex in <i>FRINGE</i> priority-queue. The priority-queue orders the vertices by the minimum weight of the edges of the vertex. And, in loop, pop a vertex from the priority-queue and put the minimum weighted edge of the vertex into the MST edge set. (All vertices of the given graph belong to MST, so the ouput is the set of edges.) The next process in the loop is that all adjacent vertices of the vertex, the destination of latest inserted edge,  insert into <i>FRINGE</i> priority-queue. <i>Prim's algorithm</i> concentrate the information of vertices. Though it control the edges, consider vertices first. <br/>
	 > &nbsp;&nbsp;The algorithm needs several datastructure, <i>priority-queue</i>. And, The input is a graph. I use my [heap implementation](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/02_Priority_Queue/01_Heap) for priority-queue and [adjacency list representation of graph](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList) for the input graph.
	 > &nbsp;&nbsp;There are a two main implementations. One is that implementing the priority-queue as <i>unordered_array</i>. Anoter is the implementation using <i>Heap</i>. Since <i>oredered_array</i> has no advantage, it is excluded.<br/><br/>
	 > - Time complexity: (discuss in theory, not aout my implementation) <br/>&nbsp;&nbsp; In the first implementation, The algorithm runs in <i>O(V|<sup>2</sup>) time</i>, where <i>V</i> is the set of vertices. The dominative operation is searching the vertex, which has the minimum weighted incident edge from a vertex of <i>FRINGE</i>. It runs in <i>O(|V|)</i> time by each iteration. So, the time complexity is <i>O(|V|)</i>.<br/>
	 > &nbsp;&nbsp;The second implementation, using <i>Heap</i>. The searching operation runs in <i>O(log n)</i> time. And, since each edges can be considered from source and destination, the keys that mean the minimum weight of all edges from a vertex can be updated. <i>DecreasKey</i> of <i>Heap</i> runs in <i>O(log n)</i> time. So, the total time complexity of updating keys is <i>O(|E|log n)</i>, where <i>E</i> is the set of edges. Since the number of vertices of a connected graph is <i>O(|E|)</i>,  $$using\ unordered\_array=O(|V|^2)$$ $$using\ heap=O(|V| log |V| + |E|log |V|) = O(|E| log |V|)$$<br/>
	 > - Space complexity: <br/>&nbsp;&nbsp; Regardless how to implement <i>FRINGE</i> priority-queue, the priority-queue has <i>O(|V|)</i> elements. $$O(|V|)$$

<br/><br/>


<p id = "Kruskal_Algorithm"></p>

2. <b> Kruskal's Algorithm</b>
	 > - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp;<i>Kruskal's algorithm</i> is the algorithm to find MST. Unlike <i>Prim's algorithm</i>, <i>Kruskal's algorithm</i> focuses on the information of edges. The main idea of <i>Kruskal's algorithm</i> is that we can construct MST if we select the minimum weighted edge at each moment. So, at first, <i>Kruskal's algorithm</i> puts all edges into <i>REMAINING</i> priority-queue. In loop, pop the minimum weighted edge from the priority-queue, and if the edge doesn't make a cylce in the tree we have constructed, put it in the tree. After loop, we can get the MST. If we use <i>Disjoint Set</i>, we can easily check whether the edge selected makes a cycle. Make <i>Disjoint Set</i> using all vertices. And, in loop, check the source and the destination of the edge selected are in the same set. If they are not in the same set, they have not been connected. Then, unify the sets the vertices belong. Else, they are already connected, so just skip the edge.
	  > &nbsp;&nbsp;The algorithm needs several datastructure, <i>priority-queue</i>. And, The input is a graph. I use my [heap implementation](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/02_Priority_Queue/01_Heap) for priority-queue and [adjacency list representation of graph](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList) for the input graph. Also, I use my [disjoint set implementation](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/03_Set/01_Disjoint_Set).
	 > &nbsp;&nbsp;There are a two main implementations. One is that implementing the <i>REMAINING</i> priority-queue as <i>sorted_array</i>. Anoter is the implementation using <i>Heap</i>.<br/><br/>
	 > - Time complexity: (discuss in theory, not aout my implementation) <br/>&nbsp;&nbsp; The implementations above don't affect the time complexity of this algorithms. The dominative operations of this algorithm are <i>build the priority-queue</i>, <i>pop the minimum weighted edge from REMAINING</i>(<i>pop from the priority-queue</i>). The first operation runs in <i>O(|E|log |E|)</i> time(sorting array) or <i>O(|E|)</i> time(heap). The second operation runs once in each iteration, and the iteration runs <i>O(|V|)</i> times. So, The total time complexity of the second operation is <i>O(|E|)</i>(sorting array) or <i> O(|E|log |E|)</i>(heap). Total time complexity of this algorithm is $$O(|E|log |E|)$$<br/>
	 > &nbsp;&nbsp;The number of edges is <i>O(|V|<sup>2</sup>)</i>, since the input graph is a connectted, undirected graph. So, the time complexity of <i>Kruskal's algorithm</i> is same with <i>Prim's algorithm</i>. $$O(|E|log|E|)=O(|E|log|V|^2)=O(|E|log|V|)$$
	 > - Space complexity: <br/>&nbsp;&nbsp; Regardless how to implement <i>REMAINING</i> priority-queue, the priority-queue has <i>O(|E|)</i> elements. And, disjoint set has <i>O(|V|)</i> elements. So, $$O(|V|||E|)$$


<br/><br/>
<p id = "ShortestPath"></p>

### [Shortest Path](https://github.com/unsik6/Algorithms_Codes/tree/main/01_Algorithms/03_Graph_algorithms/02_ShortestPath)

- Shortest Path problem is one of the famous graph problems. The probelm is finding a minimum-weight path from a source vertex(or all vertices) to a destination vertex(or all vertices). Generally, it looks like the problems not depending on some properties of a given graph, such as (un)directed, acyclic. But some algorithms to solve these probelms restrict input.
- There are four types of shotest path problem.
	> 1. Single-Source Shortest Paths (SSSP): finding the shortest paths from a given specified vertex(source vertex) to all vertices.<br/><br/>
	> 2. Single-Destination Shortest Paths (SDSP): finding the shortest paths from all vertices to a given specified vertex(destinateion vertex). This problem equals SSSP. Change all direction of edges of a given graph.(If the graph is undirected, it is not needed.) Input a given destination vertex into SSSP as a source, and output the path reversed directions (distances is same).<br/><br/>
	> 3. Single-Pair Shortest Path (SPSP): finding the shortest path from a given specified vertex(source vertex) to a given specified vertex(destination vertex). This problem equals SSSP, because we get the shortest path that we want by expanding the shortest paths of each vertex. So, we have to check all shortest paths from the source vertex to all vertices in the worst case.<br/><br/>
	> 4. All-Pair Shortest Path (APSP): finding the shortest paths from all vertices to all vertices.
- The algorithms are implemented in one namespace <i>ShortestPath</i>,
-   They return different datatype. So, If you want to test the algorithm, NOT use the function named the name of algorithms. please use the function whose name starts with  _print_.

<br/><br/>

<table>
  <tr>
    <td><center><b>Problem</b></center></td>
    <td><center><b>Algorithms</b></center></td>
  </tr>
  <tr>
    <td rowspan= 2><center>Single-Source Shortest Paths(SSSP)</center> </td>
    <td><center><a href = "#Dijkstra">Dijkstra's Algorithm</a></center></td>
  </tr>
  <tr>
	  <td><center><a href = "#Bellman-Ford">Bellman-Ford's Algorithm</a></center></td>
  </tr>
  <tr>
    <td rowspan=1><center>Single-Destination Shortest Paths (SDSP)</center></td>
    <td><center> </td>
  </tr>
  <tr>
    <td rowspan= 1><center>Single-Pair Shortest Path (SPSP)</center></td>
    <td><center></center></td>
  </tr>
  <tr>
	  <td rowspan= 1><center>All-Pair Shortest Path (APSP)</center></td>
	  <td><center><a href = "#Floyd-Warshall">Floyd-Warshall's Algorithm</a></center></td>
  </tr>
</table>

<br/><br/>

<p id = "Dijkstra"></p>

1. <b> Dijkstra's Algorithm</b>
	> - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; <i>Dijkstra's algorithm</i> is one of the algorithm to solve <u>Single-Source Shortest Path (SSSP) problem</u>. Its mechanism equals <a href = "#Prim_Algorithm"><i>Prim's</i></a>. Unlike Prim’s, this algorithm considers the distance from a source vertex we have updated, when selecting a new <i>TREE</i> vertex. If the new <i>TREE</i> vertex selected, we insert the adjacent vertices to <i>FRINGE</i> priority-queue and update the distance from a source vertex of the <i>FRINGE</i> vertices already existing. If the distance of a adjacent vertex of a new <i>TREE</i> vertex already definded is longer than the new distance(the distance of the  new <i>TREE</i> vertex + the weight of edge from the new <i>TREE</i> vertex to the adjacent <i>FRINGE</i> vertex), update the distance of the adjacent <i>FRINGE</i> vertex to the new distance. If the distance of an adjacent vertex has not defined, it means the vertex is <i>UNSEEN</i>, so insert the vertex into <i>FRINGE</i> priority-queue and update the distance of the vertex to the new distance. If all distances of all vertices was initialized infinte, this process can work in same mechanism.<br/>
	 > &nbsp;&nbsp;<i>Dijkstra's algorithm</i> works well only when all edges of a given graph have nonnegative weight. Because the distances of vertices are fixed when the vertices became <i>TREE</i>, the algorithm can not update the distance of a <i>TREE</i> vertex  when the new distance decrease by a negative edge. You know that the distances of vertices only increase from a distance of a <i>TREE</i> vertex in this algorithm.<br/>
	 > &nbsp;&nbsp;The algorithm needs several datastructure, <i>priority-queue</i>. And, The input is a graph. I use my [heap implementation](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/02_Priority_Queue/01_Heap) for priority-queue and [adjacency list representation of graph](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList) for the input graph.
	 > &nbsp;&nbsp;There are a two main implementations. One is that implementing the priority-queue as <i>unordered_array</i>. Anoter is the implementation using <i>Heap</i>. Since <i>oredered_array</i> has no advantage, it is excluded.<br/><br/>
	 > - Time complexity: (discuss in theory, not aout my implementation) <br/>&nbsp;&nbsp; In the first implementation, The algorithm runs in <i>O(V|<sup>2</sup>) time</i>, where <i>V</i> is the set of vertices. The dominative operation is searching the vertex, which has the minimum weighted incident edge from a vertex of <i>FRINGE</i>. It runs in <i>O(|V|)</i> time by each iteration. So, the time complexity is <i>O(|V|)</i>.<br/>
	 > &nbsp;&nbsp;The second implementation, using <i>Heap</i>. The searching operation runs in <i>O(log n)</i> time. And, since each edges can be considered from source and destination, the keys that mean the minimum weight of all edges from a vertex can be updated. <i>DecreasKey</i> of <i>Heap</i> runs in <i>O(log n)</i> time. So, the total time complexity of updating keys is <i>O(|E|log n)</i>, where <i>E</i> is the set of edges. Since the number of vertices of a connected graph is <i>O(|E|)</i>,  $$using\ unordered\_array=O(|V|^2)$$ $$using\ heap=O(|V| log |V| + |E|log |V|) = O(|E| log |V|)$$ &nbsp;&nbsp;And, the number of vertices on the shortest path can't be more than the number of vertex of a given graph. So, printing the path runs in <i>O(|V|)</i> time.
	 > - Space complexity: <br/>&nbsp;&nbsp; Regardless how to implement <i>FRINGE</i> priority-queue, the priority-queue has <i>O(|V|)</i> elements. $$O(|V|)$$

<br/>

<p id = "Bellman-Ford"></p>

2. <b> Bellman-Ford's algorithm</b>
	> - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; <i>Bellman-Ford's algorithm</i> is one of the algorithm to solve <u>Single-Source Shortest Path (SSSP) problem</u>.  A given graph is a directed, weighted graph.  Unlike <i>Dijkstra's algorithm</i>, moreover, a given graph can have negative weighted edges. But if there are negative weighted cycle, this algorithm can't work well, since the paths that the part of is in negative weighted cycle get less weight more and more. So, the path can not indicate the 'shortest' path.<br/>
	 &nbsp;&nbsp;<i>Bellman-Ford's algorithm</i> uses the property about the shortest path. Since the shortest path has to be a simple path, the maximum number of vertices of path is <i>|V|</i>. So, except a source vertex, update the distances of vertices <i>|V| - 1</i> times using all edges. This algorithm use <i>relaxation</i> like <i>Dijkstra's algorithm</i>.<br/>
	 > &nbsp;&nbsp;The input is a graph. I use my  [adjacency list representation of graph](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList) for the input graph.<br/><br/>
	 > - Time complexity: (discuss in theory, not aout my implementation) <br/>&nbsp;&nbsp; This algorithm iterates updating all distances of all vertices(except source vertex) <i>|V| - 1</i> times. Since, updating the distances uses all edges, <i>|E|</i> iterations run in each outer iteration. So, the time complexity of this algorithm is $$O(|V||E|)$$<br/>
	 > - Space complexity: <br/>&nbsp;&nbsp; There are arrays storing all distances of vertices and parent vertex(previous vertex in the shortest path) of each vertix. You don't have to use both and just use arrays about what you want to ouput. Since each element of arrays indicates the information of each vertex. So, the  each array has <i>|V|</i> elements.  $$O(|V|)$$

<br/>

<p id = "Floyd-Warshall"></p>

3. <b> Floyd-Warshall's algorithm</b>
	> - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; <i>Floyd-Warshall's algorithm</i> is one of the algorithm to solve <u>All-Pair Shortest Path (APSP) problem</u>. This algorithm use a matrix of <i>|V|</i> by <i>|V|</i>. This algorithm work inserting a vertex as a waypoint into a path between vertices, which are not same with the waypoint vertex, if a new path inserted the waypoint vertex is shorter than the path that already exists. So, this algorithm checks all cases that each vertex is a waypoint to all path between all pair of vertices, and updates if a new path is shorter.<br/>
	 &nbsp;&nbsp;It is same with <i>Bellman-Ford's algorithm</i> that  a given graph to <i>Floyd-Warshall's algorithm</i> can have negative weighted edges and this algorithm can't work well if there are negative weighted cycle.<br/>
	 > &nbsp;&nbsp;The input is a graph. I use my  [adjacency list representation of graph](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList) for the input graph.<br/><br/>
	 > - Time complexity: (discuss in theory, not aout my implementation) <br/>&nbsp;&nbsp; This algorithm runs with triple-overlapping iteration. The most outer iteration changes what vertex is a waypoint. The middle iteration changes what vertex is the source vertex of the path, and The inner interation changes what vertex is the destination vertex of the path. So, the time complexity of this algorithm is  $$O(|V|^3)$$<br/>
	 > - Space complexity: <br/>&nbsp;&nbsp; There are a two-dimensional array that stores the distance of paths. The element is in the <i>i</i>th column and the <i>j</i>th row in the 2D array is the shortest path from vertex <i>i</i> to vertex <i>j</i>, So, the space complexity of this algorithm is  $$O(|V|^2)$$

<br/><br/>


# Data Structures
## Binary Search Tree

- Binary Search Tree(BST) is an useful datastructure. Its main property is the node property, <i>left_child.element <= parent.element < right_child.element</i>. It is no matter if the equality relationship with the <i>parent</i> is established with the <i>left_child</i> or <i>right_child</i>.
- In a Balanced BST, the difference between the height of the left subtree and the height of the right subtree of all nodes is not big. Therefore, the some queries of a general BST runs in <i>O(n)</i> time, where <i>n</i> is the number of nodes, the same queries of a balanced BST are more efficient.

<p id = "RB_TREE"></p>

1. [<b>Red-Black Tree</b>(https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/01_Binary_Search_Tree/01_Red_Black_Tree)
	 > - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; Red-Black Tree is one of the balenced binary search tree. Since the height of this tree is <i>O(log n)</i> when <i>n</i> is the number of the node that has a key, The queries including 'search', 'predecessor', 'successor', 'minimum(maximum)', 'insert' and 'delete' can run in <i>O(h) = O(log n)</i> time. The height of a general binary search tree is <i>O(n)</i>. Moreover, Red-Black Tree is more efficeint than AVL Tree, also one of the balenced binary search tree. In AVL Tree, the process to satisfy the balanced property in the insertion of deletion runs recursively in units of one level. But, The process, which has the same purpose, of Red-Black Tree runs recursively in units of two levels. <br/>&nbsp;&nbsp;There is Red-Black Tree class implemented using template in the "RB_Tree.h" of this repository. The node of the class has an element variable declared using template. And when a node is deleted, My Red-Black Tree uses the successor of the node which will be deleted. However,you can use the predecessor of the node that will be deleted like the pseucode of CLRS. And, you can see how Red-Black Tree works in [here](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)(using predecessor)!<br/><br/>
	 > - Time complexity: <br/>&nbsp;&nbsp;All queries can run in <i>O(h) = O(log n)</i> time. $$The\ time\ complexity\ of\ all\ queries=O(log n)$$<br/>
	 > - Space complexity: <br/>&nbsp;&nbsp;All leaves of Red-Black Tree is NIL. I implements all NIL distinctly, but they can be implemented as an integrated NIL since all operation of Red-Black Tree don't call or reference the member of NIL. $$O(n)$$


<br/><br/>

## Priority Queue


<p id = "Heap"></p>

1. [<b>Heap</b>](https://github.com/unsik6/Algorithms_Codes/blob/main/02_Data_Structures/02_Priority_Queue/01_Heap/Heap.h)
	> - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; Heap is the one of the famous data structure. Heap is the left-complete binary tree. The main property of heap is <i>par.key() <= children.key(), where the heap is Min-Heap</i>, If the heap is Max-Heap, the property is reversed. It is outstanding to implement Priority queue. Heap keeps the optimal value(minimum or maximum) at the root of heap. Since, the time complexity of <i>insert</i> and <i>removeOptimalValue(with getOptimalValue)</i> is <i>O(log n)</i>, where <i>n</i> is the number of elements, heap is used to sort in <i>O(nlog n) time</i>.<br/><br/>
	 > - Time complexity:$$Build\ Heap\ =O(n)$$ &nbsp;&nbsp;Since heap is the left-complete binary tree, the height of heap is <i>O(log n)</i>. So, $$Insert\ and\ removeOptimalValue =O(log n)$$
	 > - Space complexity: (implementation: array)<br/>&nbsp;&nbsp; Since heap is the left-complete binary tree, heap don't need empty space, altough the heap is implemented as array. So, $$O(n)$$

<br/><br/>

## Set

<p id = "DisjointSet"></p>

1. [<b>DisjointSet</b>](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/03_Set/01_Disjoint_Set)
	> - Contributor: unsik6
	 > - Reference: [TECHIE DELIGT</>](https://www.techiedelight.com/ko/disjoint-set-data-structure-union-find-algorithm/)
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; Disjoint Set(Union-Find Set) is a data structure implemented as a forest. Disjoint Set has sets that have the representative number. So, as I did, Disjoint Set can be implemented using the unordered_map<key, representative number of the set to which the key belongs>. Disjoint Set has two main operation, <i>Find</i> and <i>Union</i>. <i>Find</i> is passed a key and returns the representative of the set to wich the key belongs. <i>Union</i> is passed two keys. If the keys belong to the same set, it merges the sets.<br/><br/>
	 > - Time complexity: <br/>&nbsp;&nbsp; The time complexity of <i>Find</i> and <i>Union</i> is <i>O(n)</i>, if implemented as naive algorithm, where <i>n</i> is the number of elements. But, using <i>Path compression</i> and <i>Union by rank</i>, the time complexity is <i>amortized O(1)</i>. So, $$Find\ and\ Union =O(log n)$$<br/>
	 > - Space complexity: (implementation: unorodered_set)<br/>&nbsp;&nbsp; It just need the pair, key and representative, by each elements. And, if appling <i>Path compression</i> and <i> Union by rank</i>, we need the pair, <representativ, height of the tree representing the set> by each set. The number of sets is less than the number of elements. So, $$O(n)$$

<br/><br/>

## Graph
<p id = "Graph_AdjacencyList"></p>

1. [<b>Adjacency List representation</b>](https://github.com/unsik6/Algorithms_Codes/tree/main/02_Data_Structures/04_Graph/01_AdjacencyList)
	> - Contributor: unsik6
	 > - Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, "Introduction to algorithms<sup>3rd</sup>", 2009
	 > - Language used to implement: C++
	 > - Abstract:<br/>&nbsp;&nbsp; Adjacency List is the one of the representations of graph. The idea of this representation is storing the edges from each vector in same linked list. This representation needs less space than <i>Adjacency Matrix representation</i>.<br/>&nbsp;&nbsp; I implement that <i>std::vector<std::list<Edge*>*></i>. <i>Edge</i> is the custom class that has the pointers pointing the source vertex and the destination vertex and a weight. I implement Adjacency List as template class that need two type defined by user. The first type is the type of the element of vertices and the second type is the type of the weight of edges.<br/><br/>
	 > - Time complexity: !!! This time complexity is not about Adjacency List ADT. !!!<br/>&nbsp;&nbsp; <i>Insert vertex</i> needs that the two array is inserted each one element, so the operation runs in <i>amortized O(1)</i> time. <i>delete vertex</i> and <i>find vertex</i> by the element of vertex runs in <i>O(|V|)</i>, where <i>V</i> is the set of vertices. The operations need to find the vertex having the element we input.  <i>insert edge</i> by a weight and two elements of vertices, source vertex and destination vertex, runs in <i>O(|V|)</i> time. The operation need to find the index of  the source vertex. <i>delete edge</i> by the same parameters runs in <i>O(|V|+|E|)</i> time, where <i>E</i> is the set of edges. The operation need to visit adjacency lists of all vertices and edges. <i>find edge</i> by the same parameters runs in <i>O(degree of source vertex)</i>.<br/><br/>
	 > - Space complexity: !!! This time complexity is not about Adjacency List ADT. !!!<br/>&nbsp;&nbsp; I added one more array(<i>std::vector<Vertex*></i>) having pointers of all vertices. This array needs <i>O(|V|)</i> space. Adjacency lists of all vertices have pointers of all edges. And all adjacency lists are stored in same array. So, we need <i>O(|V| + |E|)</i> space. Since we don't discuss about the number of elements of vertex and edge, total space complexity is <i>O(|V| + |E|)</i>.

<br/><br/>
