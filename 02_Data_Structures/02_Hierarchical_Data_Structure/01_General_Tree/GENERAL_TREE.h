#pragma once
#include<iostream>

#include <vector>

template<typename T>
class GENERAL_TREE
{
// change access specifier to "public", when you test whether class name Node is work well.
private:
	class Node
	{
	private:
		T m_elem;
		Node* m_ptrParent;
		std::vector<Node*>* m_ptrVecChildren;

	public:
		Node(T _elem, Node* _par = nullptr)
			: m_elem(_elem), m_ptrParent(_par)
		{
			m_ptrVecChildren = new std::vector<Node*>();
		}
		~Node()
		{
			// Don't delete parent, Because we often access a node by parent of itself.
			if (m_ptrVecChildren != nullptr)
			{
				for (typename std::vector<GENERAL_TREE<T>::Node*>::iterator iter = m_ptrVecChildren->begin(); iter != m_ptrVecChildren->end(); iter++)
				{
					if(*iter != nullptr)
						delete* iter;
				}
				delete m_ptrVecChildren;
			}
		}

		void setElem(const T _elem) { m_elem = _elem; }
		T getElem() const { return m_elem; }
		void setPar(const Node* _par) { m_ptrParent = _par; }
		Node* getPar() const { return m_ptrParent; }

		const std::vector<Node*>* getChildrenVector() const { return m_ptrVecChildren; }
		Node* getChild(T _elem)		// This function does not return const pointer, because we often acces a child for operating all operation of the child.
		{
			for (typename std::vector<GENERAL_TREE<T>::Node*>::iterator iter = m_ptrVecChildren->begin(); iter != m_ptrVecChildren->end(); iter++)
			{
				if ((*iter)->getElem() == _elem)
				{
					return *iter;
				}
			}
			return nullptr;
		}
		void insertChild(Node* _ptrChild) {m_ptrVecChildren->push_back(_ptrChild); }
		void insertChild(T _elem) {m_ptrVecChildren->push_back(new Node(_elem, this)); }
		void deleteChild(Node* _ptrChild)
		{
			if (_ptrChild == nullptr)
			{
				std::cerr << "The given node pointer is nullptr.\n";
				return;
			}
			for (typename std::vector<GENERAL_TREE<T>::Node*>::iterator iter = m_ptrVecChildren->begin(); iter != m_ptrVecChildren->end(); iter++)
			{
				if (*iter == _ptrChild)
				{
					m_ptrVecChildren->erase(iter);
					return;
				}
			}
			
			std::cerr << "There is no node equal given one.\n";
			return;
		}
		void deleteChild(T _elem)
		{
			for (typename std::vector<GENERAL_TREE<T>::Node*>::iterator iter = m_ptrVecChildren->begin(); iter != m_ptrVecChildren->end(); iter++)
			{
				if ((*iter)->getElem() == _elem)
				{
					m_ptrVecChildren->erase(iter);
					return;
				}
			}

			std::cerr << "There is no child node equal given data.\n";
			return;
		}
	};

public:
	GENERAL_TREE() {}
	
};