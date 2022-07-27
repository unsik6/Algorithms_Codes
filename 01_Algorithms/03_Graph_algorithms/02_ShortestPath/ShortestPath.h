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

	// Floyd-Warshall Algorithm

	// D is the numeric type
	template<typename D>
	struct FW_ret
	{
		int verticesNum;
		D** distances;
		bool** isNotINF;
		vector<int>** SPs;

		FW_ret(int _vNum)
		{
			this->verticesNum = _vNum;
			this->distances = new D * [verticesNum];
			this->isNotINF = new bool* [verticesNum];
			this->SPs = new vector<int>* [verticesNum];
			for (int i = 0; i < verticesNum; i++)
			{
				this->distances[i] = new D[verticesNum]{ 0 };
				this->isNotINF[i] = new bool[verticesNum] {false};
				this->isNotINF[i][i] = true;	// (V_i -> V_i) is just 0;
				this->SPs[i] = new vector<int>[verticesNum];
				// all path from i to i consist of only i.
				SPs[i][i].push_back(i);
					
			}
		}
		~FW_ret()
		{
			for (int i = 0; i < verticesNum; i++)
			{
				delete[] distances[i];
				delete[] isNotINF[i];
				delete[] SPs[i];
			}
			delete[] distances;
			delete[] isNotINF;
			delete[] SPs;
		}
	};

	// D is the numeric type
	template<typename VT, typename ET, typename D>
	FW_ret<D>* APSP_FW(Graph_AdjacencyList<VT, ET>* _graph)
	{
		int verticesNum = _graph->getVerticesNum();

		FW_ret<D>* retStruct = new FW_ret<D>(verticesNum);
		
		// fill out the first matrix using a given graph
		for (int i = 0; i < verticesNum; i++)
		{
			for (typename Graph_AdjacencyList<VT, ET>::Edge* edge : *_graph->listPtrByRankInAL(i))
			{
				typename Graph_AdjacencyList<VT, ET>::Vertex* dstV = edge->getDst();
				int dstVIdx = -1;
				for (int v = 0; v < verticesNum; v++)
				{
					if (_graph->getVertices()->at(v) == dstV)
					{
						dstVIdx = v;
						break;
					}
				}
				// ERROR : There is wrong edge
				if (dstVIdx == -1)
					return nullptr;

				if (!retStruct->isNotINF[i][dstVIdx] || retStruct->distances[i][dstVIdx] > edge->getWeight())
				{
					retStruct->distances[i][dstVIdx] = edge->getWeight();
				}
				retStruct->isNotINF[i][dstVIdx] = true;
				retStruct->SPs[i][dstVIdx].push_back(i);
				retStruct->SPs[i][dstVIdx].push_back(dstVIdx);
			}
		}

		// iterations
		for (int k = 0; k < verticesNum; k++)
		{
			for (int i = 0; i < verticesNum; i++)
			{
				// (V_i -> V_i -> V_j) don't run.
				if (k == i)
					continue;
				for (int j = 0; j < verticesNum; j++)
				{
					// (V_i -> V_k -> V_i) don't run.
					// (V_i -> V_j -> V_j) don't run.
					if (j == i || j == k)
						continue;
					// There is no path from i to k, so we can't use V_k as the waypoint
					if (!retStruct->isNotINF[i][k])
						continue;

					if (retStruct->isNotINF[k][j])
					{
						D newDistance = retStruct->distances[i][k] + retStruct->distances[k][j];

						// i to j already exist => (V_i -> V_k -> V_j) < (V_i->V_j).
						// OR i to j is not exist => (V_i -> V_k -> V_j) is the shortest path.
						if ((retStruct->isNotINF[i][j] && newDistance < retStruct->distances[i][j])
							|| !retStruct->isNotINF[i][j])
						{
							// new path is defined.
							retStruct->distances[i][j] = newDistance;

							// Checking INF and rebuilding path process
							if (!retStruct->isNotINF[i][j])
							{
								// Path from i to j is defined.
								retStruct->isNotINF[i][j] = true;
							}
							retStruct->SPs[i][j].clear();
							for (int waypoint : retStruct->SPs[i][k])
							{
								retStruct->SPs[i][j].push_back(waypoint);
							}
							retStruct->SPs[i][j].pop_back();
							for (int waypoint : retStruct->SPs[k][j])
								retStruct->SPs[i][j].push_back(waypoint);
						}
					}
				}
			}
		}

		// negative cycle check
		// same with bellman ford but need to ceck for all vertex as source vertex.
		for (int k = 0; k < verticesNum; k++)
		{
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
					if (!retStruct->isNotINF[k][srcIdx])
						continue;
					else
					{
						int newD = retStruct->distances[k][srcIdx] + edgePtr->getWeight();

						// if dstIdx is infinite,
						if (!retStruct->isNotINF[k][dstIdx])
						{
							return nullptr;
						}
						else if (newD < retStruct->distances[k][dstIdx])
						{
							return nullptr;
						}
					}
				}
			}
		}
		
		return retStruct;
	}

	template<typename VT, typename ET, typename D>
	void print_APSP_FW(Graph_AdjacencyList<VT, ET>* _graph)
	{
		FW_ret<D>* ret = APSP_FW<VT, ET, D>(_graph);
		if (ret == nullptr)
		{
			cerr << "ERROR : Their is no return\n";
			delete ret;
			return;
		}

		cout << "The shortest paths by Floyd-Warshall\n";
		for (int i = 0; i < ret->verticesNum; i++)
		{
			cout << '[' << i << "] Source = " << _graph->vertexPtrByRankinVertices(i)->getElem() << '\n';
			for (int j = 0; j < ret->verticesNum; j++)
			{
				cout << _graph->vertexPtrByRankinVertices(i)->getElem() << " to " << _graph->vertexPtrByRankinVertices(j)->getElem() << " : ";
				if (!ret->isNotINF[i][j])
				{
					cout << "NO PATH\n";
					continue;
				}
				else
				{
					cout << "Distance = " << ret->distances[i][j] << '\n';
					cout << "Path = ";
					for (int k = 0; k < ret->SPs[i][j].size(); k++)
					{
						cout << _graph->vertexPtrByRankinVertices(ret->SPs[i][j][k])->getElem();
						if (k < ret->SPs[i][j].size() - 1)
							cout << " - ";
					}
					cout << '\n';
				}
			}
			cout << '\n';
		}

		delete ret;
	}
}