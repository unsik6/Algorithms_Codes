#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Heap
{
private:
	T* m_arr;
	int m_size = 0;
	int m_cap = 0;
	bool m_isMinHeap = true;


	void swapByIDX(int _a, int _b);
	void upHeap(int _startIdx);
	void downHeap(int _startIdx);
	
public:
	Heap();
	Heap(int _cap, bool _isMin = true);
	~Heap();

	int getSize() { return m_size; }

	T getOptimal();
	void insert(T _e);
	T removeOpt();
	void updateKey(T _target, T _revisedElem);

	void printAll();
};

template<typename T>
Heap<T>::Heap() { m_arr = nullptr; }

template<typename T>
Heap<T>::Heap(int _cap, bool _isMin) { m_arr = new T[_cap + 1]; m_cap = _cap; m_isMinHeap = _isMin; }

template<typename T>
Heap<T>::~Heap() { delete[] m_arr; }

template<typename T>
void Heap<T>::swapByIDX(int _a, int _b)
{
	T tmp = m_arr[_a];
	m_arr[_a] = m_arr[_b];
	m_arr[_b] = tmp;
}

template<typename T>
void Heap<T>::upHeap(int _startIdx)
{
	int curIdx = _startIdx;
	while (curIdx > 0)
	{
		// This is MinHeap.
		if (m_isMinHeap)
		{
			if (m_arr[curIdx] < m_arr[curIdx / 2])
				swapByIDX(curIdx, curIdx / 2);
			else return;
		}
		// This is MaxHeap.
		else
		{
			if (m_arr[curIdx / 2] < m_arr[curIdx])
				swapByIDX(curIdx, curIdx / 2);
			else return;
		}

		curIdx /= 2;
	}
}

template<typename T>
void Heap<T>::downHeap(int _startIdx)
{
	int curIdx = _startIdx;
	while (curIdx * 2 <= m_size || curIdx* 2 + 1 <= m_size)
	{
		T opt = m_arr[curIdx];
		int optIdx = curIdx;
		// This is MinHeap.
		if (m_isMinHeap)
		{
			if (m_arr[curIdx * 2] < m_arr[curIdx])
			{
				opt = m_arr[curIdx * 2];
				optIdx = curIdx * 2;
			}
			if (m_arr[curIdx * 2 + 1] < m_arr[optIdx])
			{
				opt = m_arr[curIdx * 2 + 1];
				optIdx = curIdx * 2 + 1;
			}
		}
		// This is MaxHeap.
		else
		{
			if (m_arr[curIdx] < m_arr[curIdx * 2])
			{
				opt = m_arr[curIdx * 2];
				optIdx = curIdx * 2;
			}
			if (m_arr[optIdx] < m_arr[curIdx * 2 + 1])
			{
				opt = m_arr[curIdx * 2 + 1];
				optIdx = curIdx * 2 + 1;
			}
		}

		if (optIdx == curIdx)
			return;
		else
		{
			swapByIDX(curIdx, optIdx);
			curIdx = optIdx;
		}
	}
}

template<typename T>
T Heap<T>::getOptimal()
{
	if (m_size == 0)
	{
		cerr << "EMPTY EXCEPTION\n" << endl;
		return NULL;
	}
	else
		return m_arr[1];
}

template<typename T>
void Heap<T>::insert(T _e)
{
	if (m_cap <= m_size)
	{
		cerr << "FULL EXCEPTION\n" << endl;
	}

	m_arr[++m_size] = _e;
	upHeap(m_size);
}

template <typename T>
T Heap<T>::removeOpt()
{
	if (m_size == 0)
	{
		cerr << "EMPTY EXCEPTION\n" << endl;
		return m_arr[0];	// return trash.
	}

	T ret = m_arr[1];
	m_arr[1] = m_arr[m_size--];
	downHeap(1);

	return ret;
}

template<typename T>
void Heap<T>::updateKey(T _target, T _revisedElem)
{
	int targetIdx = -1;
	for (int i = 0; i < m_size; i++)
	{
		if (m_arr[i] == _target) targetIdx = i; break;
	}
	m_arr[targetIdx] = _revisedElem;
	if (m_isMinHeap)
	{
		if (_target < _revisedElem) upHeap(targetIdx);
		else downHeap(targetIdx);
	}
	else
	{
		if (_target < _revisedElem) downHeap(targetIdx);
		else upHeap(targetIdx);
	}
}

template <typename T>
void Heap<T>::printAll()
{
	for (int i = 1; i <= m_size; i++)
	{
		cout << m_arr[i] << ' ';
	}
	cout << '\n';
}