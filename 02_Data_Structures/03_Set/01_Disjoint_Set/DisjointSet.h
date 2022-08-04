#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T>
class DisjointSet
{
private:
	// m_parent stores the representative number of the set to which T belongs.
	std::unordered_map<T, T> m_parent;

	// m_rank stores the height of the tree (implementation of set).
	std::unordered_map<T, int> m_rank;

public:
	DisjointSet() {}
	DisjointSet(T* _elemArr, size_t _size);	// _elemArr is the array of elements, _size is the size of _elemArr.
	DisjointSet(std::vector<T>* _elemVec);	// _elemArr is the std::vector of elements
	~DisjointSet() {}


	// makeSet() makes sets that include each elements of the input.
	void makeSet(T* _elemArr, size_t _size);
	void makeSet(std::vector<T>* _elemVec);

	// find() returns the representative number of the set to which the input key belons.
	T find(T _key);

	// unionSets() unifies the two set to that each input key belongs.
	void unionSets(T _key1, T _key2);

	void print();
};

template <typename T>
DisjointSet<T>::DisjointSet(T* _elemArr, size_t _size)
{
	makeSet(_elemArr, _size);
}

template <typename T>
DisjointSet<T>::DisjointSet(std::vector<T>* _elemVec)
{
	makeSet(_elemVec);
}


template <typename T>
void DisjointSet<T>::makeSet(T* _elemArr, size_t _size)
{
	for (int i = 0; i < _size; i++)
	{
		m_parent[_elemArr[i]] = _elemArr[i];
		m_rank[_elemArr[i]] = 0;
	}
}


template <typename T>
void DisjointSet<T>::makeSet(std::vector<T>* _elemVec)
{
	for (int i = 0; i < _elemVec->size(); i++)
	{
		m_parent[_elemVec->at(i)] = _elemVec->at(i);
		m_rank[_elemVec->at(i)] = 0;
	}
}

template <typename T>
T DisjointSet<T>::find(T _key)
{
	// compress the path
	if (m_parent[_key] != _key)
		m_parent[_key] = find(m_parent[_key]);

	return m_parent[_key];
}

template <typename T>
void DisjointSet<T>::unionSets(T _key1, T _key2)
{
	T repNum1 = find(_key1);
	T repNum2 = find(_key2);

	if (repNum1 == repNum2)
	{
		// They belong to the same set.
		return;
	}

	// Add the tree that has smaller height to another. It makes all trees have their height as small as possible.
	if (m_rank[repNum1] < m_rank[repNum2])
	{
		m_parent[repNum1] = repNum2;
	}
	else
	{
		m_parent[repNum2] = repNum1;
		// If the sizes of the two sets are same, unify the sets to any one and plus 1 to the dominate set.
		if (m_rank[repNum1] == m_rank[repNum2])
		{
			m_rank[repNum1] += m_rank[repNum2] + 1;
		}
	}
}

template <typename T>
void DisjointSet<T>::print()
{
	for (auto e : m_parent)
	{
		std::cout << e.first << ' ' << e.second << '\n';
	}
}

