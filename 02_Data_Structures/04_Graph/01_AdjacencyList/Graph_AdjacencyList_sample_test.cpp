#include <iostream>
#include "Heap.h"
#include "Graph_AdjacencyList.h"
using namespace std;

int main()
{
	Graph_AdjacencyList<int, int> graph;

	int V, E;
	cout << "Input the number of vertices: ";
	cin >> V;
	cout << "Input the number of Edges: ";
	cin >> E;

	for (int i = 0; i < V; i++)
	{
		int Elem;
		cout << "Input the element of vertex " << i << ": ";
		cin >> Elem;
		graph.insertVertex(Elem);
	}

	for (int i = 0; i < V; i++)
	{
		int srcElem, dstElem, weight;
		cout << "Input the src, dst, weight of edge " << i << ": ";
		cin >> srcElem >> dstElem >> weight;
		graph.insertEdge(srcElem, dstElem, weight);
	}

	graph.print();
}