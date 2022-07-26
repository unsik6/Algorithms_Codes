#pragma once
#include <iostream>
#include <stack>
#include "Heap.h"
#include "Graph_AdjacencyList.h"

namespace ShortestPath
{
	// Dijkstra algorithm
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
		if (_distanceOrPath)
		{
			delete[] SP_preVertices;
			return SPDistances;
		}
		else
		{
			delete[] SPDistances;
			return SP_preVertices;
		}
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

	// Bellman-Ford algorithm
	template<typename VT, typename ET>
	int* SSSP_BF(Graph_AdjacencyList<VT, ET>* _graph, VT* _srcElem, bool _distanceOrPath)
	{
		int verticesNum = _graph->getVerticesNum();

		// ret
		int* distances = new int[verticesNum];
		bool* isNotInfite = new bool[verticesNum] {false};	// If the distance of vertex is not infite, the distance was already updated.
		int* preVertices = new int[verticesNum];


		// find src vertex idx and initialize
		int srcVertexIdx = -1;
		for (int i = 0; i < verticesNum; i++)
		{
			if (_graph->getVertices()->at(i)->getElem() == *_srcElem)
			{
				srcVertexIdx = i;
				break;
			}
		}

		distances[srcVertexIdx] = 0;
		isNotInfite[srcVertexIdx] = true;
		preVertices[srcVertexIdx] = -1;

		for (int i = 0; i < verticesNum; i++)
		{
			for (int j = 0; j < verticesNum; j++)
			{
				for (typename Graph_AdjacencyList<VT, ET>::Edge *edgePtr : *_graph->listPtrByRankInAL(j))
				{
					typename Graph_AdjacencyList<VT, ET>::Vertex* src = edgePtr->getSrc();
					typename Graph_AdjacencyList<VT, ET>::Vertex* dst = edgePtr->getDst();

					int srcIdx = -1, dstIdx = -1;

					for (int i = 0; i < verticesNum; i++)
					{
						if (_graph->getVertices()->at(i) == src)
							srcIdx = i;
						else if (_graph->getVertices()->at(i) == dst)
							dstIdx = i;
						if (srcIdx != -1 && dstIdx != -1) break;
					}

					// ERROR: This is not correct edge.
					if (srcIdx == -1 || dstIdx == -1) return nullptr;

					// infite + edge.weight
					if (!isNotInfite[srcIdx])
						continue;
					else
					{
						int newD = distances[srcIdx] + edgePtr->getWeight();
						if (newD < distances[dstIdx] || !isNotInfite[dstIdx])
						{
							distances[dstIdx] = newD;
							preVertices[dstIdx] = srcIdx;
							if (!isNotInfite[dstIdx])
								isNotInfite[dstIdx] = true;
						}
							
					}

				}
			}
		}

		// negative cycle check
		for (int j = 0; j < verticesNum; j++)
		{
			for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(j))
			{
				typename Graph_AdjacencyList<VT, ET>::Vertex* src = edgePtr->getSrc();
				typename Graph_AdjacencyList<VT, ET>::Vertex* dst = edgePtr->getDst();

				int srcIdx = -1, dstIdx = -1;

				for (int i = 0; i < verticesNum; i++)
				{
					if (_graph->getVertices()->at(i) == src)
						srcIdx = i;
					else if (_graph->getVertices()->at(i) == dst)
						dstIdx = i;
					if (srcIdx != -1 && dstIdx != -1) break;
				}

				// ERROR: This is not correct edge.
				if (srcIdx == -1 || dstIdx == -1) return nullptr;

				// If newD is less than dst.D => negative cycle
				// if distance[srcIdx] == infinite, then skip
				if (!isNotInfite[srcIdx])
					continue;
				else 
				{
					int newD = distances[srcIdx] + edgePtr->getWeight();

					// if dstIdx is infinite,
					if (!isNotInfite[dstIdx])
					{
						return nullptr;
					}
					else if (newD < distances[dstIdx])
					{
						return nullptr;
					}
				}
			}
		}

		delete[] isNotInfite;
		if (_distanceOrPath)
		{
			delete[] preVertices;
			return distances;
		}
		else
		{
			delete[] distances;
			return preVertices;
		}
	}

	template<typename VT, typename ET>
	void printSSSP_BF(Graph_AdjacencyList<VT, ET>* _graph, VT* _srcElem)
	{
		int* distances = SSSP_BF(_graph, _srcElem, true);
		int* path = SSSP_BF(_graph, _srcElem, false);

		stack<int> pathStack;
		if (distances == nullptr || path == nullptr)
		{
			cout << "ERROR\n";
			return;
		}

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