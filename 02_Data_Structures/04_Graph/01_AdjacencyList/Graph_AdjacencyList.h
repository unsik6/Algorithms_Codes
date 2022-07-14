#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename VT, typename ET>
class Graph_AdjacencyList
{
public:
	class Vertex
	{
	private:
		VT m_elem;

	public:
		Vertex(VT _e = NULL) { m_elem = _e; }

		VT getElem() { return m_elem; }
		void setID(VT _e) { m_elem = _e; }
	};

	class Edge
	{
	private:
		Vertex *m_src, *m_dst;
		ET m_wt;

	public:
		Edge() { m_src = m_dst = nullptr; m_wt = NULL; }
		Edge(Vertex* _src, Vertex* _dst, ET _wt) { m_src = _src; m_dst = _dst; m_wt = _wt; }
		bool operator <(const Edge& _a)
		{
			return this->m_wt < _a.m_wt;
		}

		Vertex* getSrc() { return m_src; }
		Vertex* getDst() { return m_dst; }
		ET getWeight() { return m_wt; }
	};

private:
	// just keep the information of vertices
	vector<Vertex*> m_vertices;

	// adjacencyList
	vector<list<Edge*>*> m_adjacencyList;
	
public:
	Graph_AdjacencyList() {}
	~Graph_AdjacencyList();

	size_t getVerticesNum() { return m_vertices.size(); }

	// vertex Function
	Vertex* vertexPtrByRankinVertices(int _idx);
	list<Edge*>* listPtrByRankInAL(int _idx);

	// Vertex Function
	void insertVertex(VT _vElem);
	void deleteVertex(VT _vElem);
	Vertex* findVertex(VT _vElem);

	// Edge Function
	void insertEdge(VT _srcVElem, VT _dstVElem, ET _eWt);
	void deleteEdge(VT _srcVElem, VT _dstVElem, ET _eWt);
	void deleteEdge(VT _srcVElem, VT _dstVElem);
	Edge* findEdge(VT _srcVElem, VT _dstVElem, ET _eWt);
	Edge* findEdge(VT _srcVElem, VT _dstVElem);

	void print();	
};

template<typename VT, typename ET>
Graph_AdjacencyList<VT, ET>::~Graph_AdjacencyList()
{
	for (int i = 0; i < m_vertices.size(); i++)
	{
		while (!m_adjacencyList[i]->empty())
		{
			Edge* tmp = m_adjacencyList[i]->front();
			m_adjacencyList[i]->pop_front();
			delete tmp;
		}
		delete m_adjacencyList[i];
		delete m_vertices[i];
	}
}
template<typename VT, typename ET>
typename Graph_AdjacencyList<VT, ET>::Vertex* Graph_AdjacencyList<VT, ET>::vertexPtrByRankinVertices(int _idx)
{
	return m_vertices[_idx];
}


template<typename VT, typename ET>
list<typename Graph_AdjacencyList<VT, ET>::Edge*>* Graph_AdjacencyList<VT, ET>::listPtrByRankInAL(int _idx)
{
	return m_adjacencyList[_idx];
}

template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::insertVertex(VT _velem)
{
	m_vertices.push_back(new Vertex(_velem));
	m_adjacencyList.push_back(new list<Edge*>);
}

template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::deleteVertex(VT _vElem)
{
	// find the index of the vertex we want to delete
	int vIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
	{
		if (m_vertices[i]->getElem() == _vElem)
		{
			vIdx = i;
			break;
		}
	}

	// Not Found Exception
	if (vIdx == -1) return;


	// delete all edges to the vertex we want to delete.
	for (int i = 0; i < m_adjacencyList.size(); i++)
	{
		if (i == vIdx) continue;
		
		for (int j = 0; j < m_adjacencyList[i]->size(); j++)
		{
			for (Edge* edge : m_adjacencyList[i])
			{
				if (edge->getDst() == m_vertices[vIdx])
				{
					m_adjacencyList[i]->remove(edge);
					delete edge;
				}
			}
		}
	}

	// delete all edges from the vertex we want to delete. And delete the adjacency list of the vertex
	for (Edge* edge : m_adjacencyList[vIdx])
		delete edge;
	delete m_adjacencyList[vIdx];
	m_adjacencyList.erase(m_adjacencyList.begin() + vIdx);

	// delete the vertex
	m_vertices.erase(m_vertices.begin() + vIdx);
}
template<typename VT, typename ET>
typename Graph_AdjacencyList<VT, ET>::Vertex* Graph_AdjacencyList<VT, ET>::findVertex(VT _vElem)
{
	for (int i = 0; i < m_vertices.size(); i++)
	{
		if (m_vertices[i]->getElem() == _vElem)
		{
			return m_vertices[i];
		}
	}

	return nullptr;
}
template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::insertEdge(VT _srcVElem, VT _dstVElem, ET _eWt)
{
	Vertex* srcPtr = findVertex(_srcVElem);
	Vertex* dstPtr = findVertex(_dstVElem);

	// Not Found Exception
	if (srcPtr == nullptr || dstPtr == nullptr)
		return;

	// Find the indices of the src vertex.
	int srcIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
		if (m_vertices[i] == srcPtr) srcIdx = i;

	// insertEdge
	m_adjacencyList[srcIdx]->push_back(new Edge(srcPtr, dstPtr, _eWt));	
}

template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::deleteEdge(VT _srcVElem, VT _dstVElem, ET _eWt)
{
	Vertex* srcPtr = findVertex(_srcVElem);
	Vertex* dstPtr = findVertex(_dstVElem);

	// Not Found Exception
	if (srcPtr == nullptr || dstPtr == nullptr)
		return;

	// Find the indices of the src vertex.
	int srcIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
		if (m_vertices[i] == srcPtr) srcIdx = i;

	for (Edge* edge : m_adjacencyList[srcIdx])
	{
		if (edge->getDst() == dstPtr && edge->getWeight() == _eWt)
		{
			Edge* tmp = edge;
			m_adjacencyList[srcIdx]->remove(edge);
			delete tmp;
		}
	}
}

template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::deleteEdge(VT _srcVElem, VT _dstVElem)
{
	Vertex* srcPtr = findVertex(_srcVElem);
	Vertex* dstPtr = findVertex(_dstVElem);

	// Not Found Exception
	if (srcPtr == nullptr || dstPtr == nullptr)
		return;

	// Find the indices of the src vertex.
	int srcIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
		if (m_vertices[i] == srcPtr) srcIdx = i;

	for (Edge* edge : m_adjacencyList[srcIdx])
	{
		if (edge->getDst() == dstPtr)
		{
			m_adjacencyList[srcIdx]->erase(edge);
			delete edge;
		}
	}
}

template<typename VT, typename ET>
typename Graph_AdjacencyList<VT, ET>::Edge* Graph_AdjacencyList<VT, ET>::findEdge(VT _srcVElem, VT _dstVElem, ET _eWt)
{
	Vertex* srcPtr = findVertex(_srcVElem);
	Vertex* dstPtr = findVertex(_dstVElem);

	// Not Found Exception
	if (srcPtr == nullptr || dstPtr == nullptr)
		return;

	// Find the indices of the src vertex.
	int srcIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
		if (m_vertices[i] == srcPtr) srcIdx = i;

	for (Edge* edge : m_adjacencyList[srcIdx])
	{
		if (edge->getDst() == dstPtr && edge->getWeight() == _eWt)
		{
			return edge;
		}
	}

	return nullptr;
}

template<typename VT, typename ET>
typename Graph_AdjacencyList<VT, ET>::Edge* Graph_AdjacencyList<VT, ET>::findEdge(VT _srcVElem, VT _dstVElem)
{
	Vertex* srcPtr = findVertex(_srcVElem);
	Vertex* dstPtr = findVertex(_dstVElem);

	// Not Found Exception
	if (srcPtr == nullptr || dstPtr == nullptr)
		return;

	// Find the indices of the src vertex.
	int srcIdx = -1;
	for (int i = 0; i < m_vertices.size(); i++)
		if (m_vertices[i] == srcPtr) srcIdx = i;

	for (Edge* edge : m_adjacencyList[srcIdx])
	{
		if (edge->getDst() == dstPtr)
		{
			return edge;
		}
	}

	return nullptr;
}

template<typename VT, typename ET>
void Graph_AdjacencyList<VT, ET>::print()
{
	cout << "Vertex And Edges : \n";
	for (int i = 0; i < m_vertices.size(); i++)
	{
		cout << "vertex " << i << "(" << m_vertices[i]->getElem() << ") : ";
		for (Edge* edge : *m_adjacencyList[i])
		{
			cout << "(dst: " << edge->getDst()->getElem() << ", Weight: " << edge->getWeight() << ") ";
		}

		cout << '\n';
	}
	cout << '\n';

	
}