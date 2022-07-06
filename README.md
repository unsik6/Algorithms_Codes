
# Algorithms_Codes

# Outline

&nbsp;&nbsp;This repository contains the source codes about implementation of some algorithms or data structurses that I need to know to study something about an algorithm. The source codes are written by me, referencing the original paper sugesting the source codes ore some papers referencing the original paper.

# Algorithms
&nbsp;&nbsp;Implementations of Algorithms using C++.
## Pattern Matching
&nbsp;&nbsp;Pattern matching problem is the problem that finds multiple or single pattern in multiple of single given text.
1. Aho-Corasick Automata
	> - Reference: Alfred V. Aho and Margaret J. Corasick, "Efficient String Matching: An Aid to Bibliographic Search", ACM, 1975
	> - Time complexity: <br/>preprocessing to construct the automata using all patterns needs time linear to sum the length of all patterns. And, Searching patterns in a given text needs time linear to the length of the text. $$O(\sum{|pattern|}  + n)\,,where\,n\,is\,the\,length\,of\,the\,text$$
	> &nbsp;&nbsp; Aho-Corasck Automata is the deterministic automata to find all location of multiple patterns in a given text. Preprocessing patterns constructs the automata looked like a trie. Next, put a give text, the string in which we want to find patterns, in the automata.
<br/>

