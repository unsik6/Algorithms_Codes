#pragma once
#include <iostream>
#include <stack>
#include "Heap.h"
#include "Graph_AdjacencyList.h"

namespace ShortestPath
{
	// Dijkstra
	enum class DijkstraVertexFlag { UNSEEN, FRINGE, TREE };

	template<typename VT, typename ET>
	struct lightestEdgeAndVertex
	{
		int vertexIdx = -1;
		int prevIdx = -1;
		ET shortestDistance = NULL;
		typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr = nullptr;

		~lightestEdgeAndVertex()
		{
			edgePtr = nullptr;
		}

		bool operator < (const lightestEdgeAndVertex& _a) { return this->shortestDistance < _a.shortestDistance; }

		// == operator check only that two sturct are not different.
		bool operator ==(const lightestEdgeAndVertex& _a) { return this->vertexIdx == _a.vertexIdx; }

		void operator =(const lightestEdgeAndVertex& _a)
		{
			this->vertexIdx = _a.vertexIdx;
			this->prevIdx = _a.prevIdx;
			this->shortestDistance = _a.shortestDistance;
			typename Graph_AdjacencyList<VT, ET>::Edge* copy
				= new typename Graph_AdjacencyList<VT, ET>::Edge(_a.edgePtr->getSrc(), _a.edgePtr->getDst(), _a.edgePtr->getWeight());

			this->edgePtr = copy;
		}
	};

	template<typename VT, typename ET>
	int* SSSP_Dijkstra(Graph_AdjacencyList<VT, ET>* _graph, VT* _srcElem, bool _distanceOrPath)
	{
		// get the number of vertices
		int verticesNum = _graph->getVerticesNum();

		// return [vertex index - the distance of each vertex] or [vertex index - the previous vertex index on path]
		int* SPDistances = new int[verticesNum];
		int* SP_preVertices = new int[verticesNum];

		int srcVertexIdx = -1;
		for (int i = 0; i < verticesNum; i++)
		{
			if (_graph->getVertices()->at(i)->getElem() == *_srcElem)
			{
				srcVertexIdx = i;
				break;
			}
		}

		// NOT FOUND EXCEPTION
		if (srcVertexIdx == -1) return nullptr;

		// The flag array of vertices.
		DijkstraVertexFlag* verticesFlags = new DijkstraVertexFlag[verticesNum];
		for (int i = 0; i < verticesNum; i++)
			verticesFlags[i] = DijkstraVertexFlag::UNSEEN;
		verticesFlags[srcVertexIdx] = DijkstraVertexFlag::TREE;

		// Initialize
		SPDistances[srcVertexIdx] = 0;
		SP_preVertices[srcVertexIdx] = -1;

		// Heap to store FRINGE vertices to get the lightest edge of FIRNGE vertices.
		Heap<lightestEdgeAndVertex<VT, ET>> fringesHeap(verticesNum);
		for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(srcVertexIdx))
		{
			for (int i = 0; i < verticesNum; i++)
			{
				if (_graph->vertexPtrByRankinVertices(i) == edgePtr->getDst())
				{
					verticesFlags[i] = DijkstraVertexFlag::FRINGE;
					lightestEdgeAndVertex<VT, ET> adj{ i, srcVertexIdx, edgePtr->getWeight(), edgePtr };
					fringesHeap.insert(adj);
					break;
				}
			}
		}

		while (fringesHeap.getSize() > 0)
		{
			lightestEdgeAndVertex<VT, ET> adj = fringesHeap.removeOpt();
			verticesFlags[adj.vertexIdx] = DijkstraVertexFlag::TREE;
			SPDistances[adj.vertexIdx] = adj.shortestDistance;
			SP_preVertices[adj.vertexIdx] = adj.prevIdx;
			
			for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(adj.vertexIdx))
			{
				for (int i = 0; i < verticesNum; i++)
				{
					if (_graph->vertexPtrByRankinVertices(i) == edgePtr->getDst())
					{
						// insert new fringe
						if (verticesFlags[i] == DijkstraVertexFlag::UNSEEN)
						{
							verticesFlags[i] = DijkstraVertexFlag::FRINGE;
							lightestEdgeAndVertex<VT, ET> new_adj{ i, adj.vertexIdx, adj.shortestDistance + edgePtr->getWeight(), edgePtr };
							fringesHeap.insert(new_adj);
						}
						// decrease lightest weight of a fringe vertex
						else if (verticesFlags[i] == DijkstraVertexFlag::FRINGE)
						{
							lightestEdgeAndVertex<VT, ET> ori{ i };
							lightestEdgeAndVertex<VT, ET> new_adj{ i, adj.vertexIdx, adj.shortestDistance + edgePtr->getWeight(), edgePtr };
							for (int j = 1; j <= fringesHeap.getSize(); j++)
							{
								if (fringesHeap.getArr()[j] == ori)
								{
									ori = fringesHeap.getArr()[j];
									break;
								}

							}
							if (new_adj < ori)
								fringesHeap.updateKey(ori, new_adj);
						}

						break;
					}
				}
			}
			
		}

		delete[] verticesFlags;
		if (_distanceOrPath)	return SPDistances;
		else return SP_preVertices;
	}

	template<typename VT, typename ET>
	void printSSSP_Dijkstra(Graph_AdjacencyList<VT, ET>* _graph, VT* _srcElem)
	{
		int* distances = SSSP_Dijkstra(_graph, _srcElem, true);
		int* path = SSSP_Dijkstra(_graph, _srcElem, false);

		stack<int> pathStack;

		cout << "Distance and Path from " << *_srcElem << '\n';
		for (int i = 0; i < _graph->getVerticesNum(); i++)
		{
			cout << *_srcElem << " To " << _graph->getVertices()->at(i)->getElem() << '\n';
			cout << "Distance: " << distances[i] << "\nPath: ";
			pathStack.push(i);
			while (true)
			{
				int topVertexIdx = pathStack.top();

				if (path[topVertexIdx] == -1) break;
				pathStack.push(path[topVertexIdx]);
			}
			while (true)
			{
				cout << _graph->getVertices()->at(pathStack.top())->getElem();
				pathStack.pop();

				if (pathStack.empty())
					break;
				else cout << " - ";
			}
			cout << '\n';
		}
	}
}