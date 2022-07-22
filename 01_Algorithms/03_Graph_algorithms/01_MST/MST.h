#pragma once
#include <iostream>
#include "Heap.h"
#include "DisjointSet.h"
#include "Graph_AdjacencyList.h"

namespace MST
{
	// Prim
	enum class primVertexFlag { UNSEEN, FRINGE, TREE };

	template<typename VT, typename ET>
	struct lightestEdgeAndVertex
	{
		int vertexIdx = -1;
		ET lightestWeight = NULL;
		typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr = nullptr;

		~lightestEdgeAndVertex()
		{
			edgePtr = nullptr;
		}
		
		bool operator < (const lightestEdgeAndVertex& _a) { return this->lightestWeight < _a.lightestWeight; }

		// == operator check only that two sturct are not different.
		bool operator ==(const lightestEdgeAndVertex& _a) { return this->vertexIdx == _a.vertexIdx; }

		void operator =(const lightestEdgeAndVertex& _a)
		{
			this->vertexIdx = _a.vertexIdx;
			this->lightestWeight = _a.lightestWeight;
			typename Graph_AdjacencyList<VT, ET>::Edge* copy
				= new typename Graph_AdjacencyList<VT, ET>::Edge(_a.edgePtr->getSrc(), _a.edgePtr->getDst(), _a.edgePtr->getWeight());

			this->edgePtr = copy;
		}
	};

	template<typename VT, typename ET>
	typename Graph_AdjacencyList<VT, ET>::Edge** MST_Prim(Graph_AdjacencyList<VT, ET>* _graph, VT* _rootElem)
	{
		// the number of vertices.
		int vertexNum = (int)_graph->getVerticesNum();

		// To return
		int retIdx = 0;
		typename Graph_AdjacencyList<VT, ET>::Edge** retEdges = new typename Graph_AdjacencyList<VT, ET>::Edge*[vertexNum - 1];

		// Select the root of MST.
		int rootIdx = -1;
		if (_rootElem == nullptr)
		{
			rootIdx = 0;
		}
		else
		{
			for (int i = 0; i < vertexNum; i++)
			{
				if (_graph->vertexPtrByRankinVertices(i)->getElem() == *_rootElem)
				{
					rootIdx = i;
				}
			}
		}
		// The input root does not exist.
		if (rootIdx == -1) return nullptr;

		// The flag array of vertices.
		primVertexFlag* verticesFlags = new primVertexFlag[vertexNum];
		for (int i = 0; i < vertexNum; i++)
			verticesFlags[i] = primVertexFlag::UNSEEN;
		verticesFlags[rootIdx] = primVertexFlag::TREE;

		// Keep the min heap about the edges of fringe vertices.
		Heap<lightestEdgeAndVertex<VT, ET>> fringesHeap(vertexNum, true);

		// insert the adjacent vertices from the root.
		for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(rootIdx))
		{
			for (int i = 0; i < vertexNum; i++)
			{
				if (_graph->vertexPtrByRankinVertices(i) == edgePtr->getDst())
				{
					verticesFlags[i] = primVertexFlag::FRINGE;
					lightestEdgeAndVertex<VT, ET> adj{ i, edgePtr->getWeight(), edgePtr };
					fringesHeap.insert(adj);
					break;
				}
			}
		}

		while (fringesHeap.getSize() > 0)
		{
			lightestEdgeAndVertex<VT, ET> adj = fringesHeap.removeOpt();
			verticesFlags[adj.vertexIdx] = primVertexFlag::TREE;
			retEdges[retIdx++] = adj.edgePtr;

			for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(adj.vertexIdx))
			{
				for (int i = 0; i < vertexNum; i++)
				{
					if (_graph->vertexPtrByRankinVertices(i) == edgePtr->getDst())
					{
						// insert new fringe
						if (verticesFlags[i] == primVertexFlag::UNSEEN)
						{
							verticesFlags[i] = primVertexFlag::FRINGE;
							lightestEdgeAndVertex<VT, ET> new_adj{ i, edgePtr->getWeight(), edgePtr };
							fringesHeap.insert(new_adj);
						}
						// decrease lightest weight of a fringe vertex
						else if (verticesFlags[i] == primVertexFlag::FRINGE)
						{
							lightestEdgeAndVertex<VT, ET> ori{ i };
							lightestEdgeAndVertex<VT, ET> new_adj{ i, edgePtr->getWeight(), edgePtr };
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

			if (retIdx == vertexNum) break;
		}

		delete verticesFlags;

		return retEdges;
	}

	template<typename VT, typename ET>
	void printMST_Prim(Graph_AdjacencyList<VT, ET>* _graph, VT* _rootElem)
	{
		typename Graph_AdjacencyList<VT, ET>::Edge** mst = MST_Prim(_graph, _rootElem);
		for (int i = 0; i < _graph->getVerticesNum() - 1; i++)
		{
			cout << "(src: "
				<< mst[i]->getSrc()->getElem() << ", dst: " << mst[i]->getDst()->getElem()
				<< ", Weight : " << mst[i]->getWeight() << ") ";
		}
	}



	// Kruskal
	template<typename VT, typename ET>
	typename Graph_AdjacencyList<VT, ET>::Edge* MST_Kruskal(Graph_AdjacencyList<VT, ET>* _graph)
	{
		int vertexNum = (int)_graph->getVerticesNum();

		// To return
		int retIdx = 0;
		typename Graph_AdjacencyList<VT, ET>::Edge* retEdges = new typename Graph_AdjacencyList<VT, ET>::Edge[vertexNum - 1];

		// Set the min-heap of Edges
		int edgeNum = 0;
		for (int i = 0; i < vertexNum; i++)
		{
			edgeNum += _graph->listPtrByRankInAL(i)->size();
		}
		Heap<typename Graph_AdjacencyList<VT, ET>::Edge> REMAINING_Edges(edgeNum, true);
		for (int i = 0; i < vertexNum; i++)
		{
			for (typename Graph_AdjacencyList<VT, ET>::Edge* edgePtr : *_graph->listPtrByRankInAL(i))
			{
				REMAINING_Edges.insert(*edgePtr);
			}
		}
		// Set the disjointSet of vertices
		vector<VT> VTVec;
		for (int i = 0; i < vertexNum; i++)
			VTVec.push_back(_graph->getVertices()->at(i)->getElem());
		DisjointSet<VT> vertexCycleTable(&VTVec);

		// loop
		while (REMAINING_Edges.getSize() > 0 || retIdx < vertexNum - 1)
		{
			typename Graph_AdjacencyList<VT, ET>::Edge minEdge = REMAINING_Edges.removeOpt();
			typename Graph_AdjacencyList<VT, ET>::Vertex* src = minEdge.getSrc();
			typename Graph_AdjacencyList<VT, ET>::Vertex* dst = minEdge.getDst();

			if (vertexCycleTable.find(src->getElem()) == vertexCycleTable.find(dst->getElem()))
				continue;
			else
			{
				vertexCycleTable.unionSets(src->getElem(), dst->getElem());
				retEdges[retIdx++] = minEdge;
			}
		}

		return retEdges;
	}

	template<typename VT, typename ET>
	void printMST_Kruskal(Graph_AdjacencyList<VT, ET>* _graph)
	{
		typename Graph_AdjacencyList<VT, ET>::Edge* mst = MST_Kruskal(_graph);
		for (int i = 0; i < _graph->getVerticesNum() - 1; i++)
		{
			cout << "(src: "
				<< mst[i].getSrc()->getElem() << ", dst: " << mst[i].getDst()->getElem()
				<< ", Weight : " << mst[i].getWeight() << ") ";
		}
	}
};

