#include <iostream>
#include "Graph_AdjacencyList.h"
#include "ShortestPath.h"

using namespace std;




int main()
{
	Graph_AdjacencyList<char, int> graph;

	int V, E;
	cout << "Input the number of vertices: ";
	cin >> V;
	cout << "Input the number of Edges: ";
	cin >> E;

	for (int i = 0; i < V; i++)
	{
		char Elem;
		cout << "Input the element of vertex " << i << ": ";
		cin >> Elem;
		graph.insertVertex(Elem);
	}

	for (int i = 0; i < E; i++)
	{
		char srcElem, dstElem; int weight;
		cout << "Input the src, dst, weight of edge " << i << ": ";
		cin >> srcElem >> dstElem >> weight;
		graph.insertEdge(srcElem, dstElem, weight);
	}

	graph.print();

	cout << "What is an element of source? ";
	char srcElem;
	cin >> srcElem;

	ShortestPath::printSSSP_Dijkstra<char, int>(&graph, &srcElem);
}