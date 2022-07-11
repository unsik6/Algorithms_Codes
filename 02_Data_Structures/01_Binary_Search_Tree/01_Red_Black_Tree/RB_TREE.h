#pragma
#include <iostream>
using namespace std;

template <typename T>
class RB_TREE
{
	class Node
	{
		T m_elem;
		bool m_RB;	// true = red, false = black;
		Node* m_parent = nullptr; Node* m_left = nullptr; Node* m_right = nullptr;

	public:
		Node(T _elem, bool _rb, Node* _p = nullptr, Node* _l = nullptr, Node* _r = nullptr) : m_elem(_elem), m_RB(_rb), m_parent(_p), m_left(_l), m_right(_r) {}
		~Node()
		{
			if (m_left != nullptr)
			{
				delete m_left;
			}
			if (m_right != nullptr)
			{
				delete m_right;
			}
		}

		void setRB(bool _rb) { m_RB = _rb; }
		bool getRB() { return m_RB; }
		void setPar(Node* _p) { m_parent = _p; }
		Node* getPar() { return m_parent; }
		void setLeft(Node* _l) { m_left = _l; }
		Node* getLeft() { return m_left; }
		void setRight(Node* _r) { m_right = _r; }
		Node* getRight() { return m_right; }
		void setElem(T _e) { m_elem = _e; }
		T getElem() { return m_elem; }

		bool operator < (const Node& _a)
		{
			return this->m_elem < _a.m_elem;
		}

		bool operator ==(const Node& _a)
		{
			return this->m_elem == _a.m_elem;
		}

		int getDepth()
		{
			Node* curNode = this;
			int depth = 0;
			while (curNode->getPar() != nullptr)
			{
				curNode = curNode->getPar();
				depth++;
			}
			return depth;
		}
	};

private:
	Node* m_root;

public:
	RB_TREE()
	{
		m_root = nullptr;
	}
	RB_TREE(T _rElem)
	{
		Node* root = new Node(_rElem, false);
		m_root = root;
	}
	~RB_TREE()
	{
		delete m_root;
	}

	Node* getRoot() { return m_root; }
	Node* setRoot(Node* _r) { m_root = _r; }

	Node* search(T _tar)
	{
		Node* curNode = m_root;
		while (curNode != nullptr)
		{
			if (curNode->getElem() < _tar)
				curNode = curNode->getRight();
			else if (curNode->getElem() == _tar)
				return curNode;
			else
				curNode = curNode->getLeft();
		}

		// Fail to search
		return nullptr;
	}

	void insertNode(T _e)
	{
		// insert Root
		if (m_root == nullptr)
		{
			m_root = new Node(_e, false);
			return;
		}

		Node* newNode = new Node(_e, true);

		// find the first position of newNode and the parent of newNode;
		Node* curNode = m_root;
		Node* parNode = nullptr;
		while (true)
		{
			if (*curNode < *newNode)
			{
				parNode = curNode;
				curNode = curNode->getRight();
				if (curNode == nullptr)
				{
					parNode->setRight(newNode);
					newNode->setPar(parNode);
					break;
				}
			}
			else
			{
				parNode = curNode;
				curNode = curNode->getLeft();

				if (curNode == nullptr)
				{
					parNode->setLeft(newNode);
					newNode->setPar(parNode);
					break;
				}
			}
		}

		if(parNode != m_root) fix(newNode, parNode);
	}

	private:
	// if Double RED occurs, we need to set the part of RB Tree to satisfy the property of RB Tree.
	void fix(Node* _cur, Node* _p)
	{
		// If RB of the parent node of the node we want to insert is true(=red), Double RED occurs.
		if (_p->getRB())
		{
			// we need the uncle node for restructuring or recoloring when Double RED occurs.
			Node* uncleNode = nullptr;
			Node* grandNode = _p->getPar();
			if (grandNode->getLeft() == _p)
				uncleNode = grandNode->getRight();
			else
				uncleNode = grandNode->getLeft();

			bool RBOfUncle = true;
			if (uncleNode == nullptr)
				RBOfUncle = false;
			else if (!uncleNode->getRB())
				RBOfUncle = false;

			// Recoloring
			if (RBOfUncle)
			{
				recoloring(_p, uncleNode, grandNode);
				if (grandNode != m_root)
				{
					if (grandNode->getPar()->getRB())
						fix(grandNode, grandNode->getPar());
				}
			}
			// Restructuring
			else
			{
				restructuring(_cur, _p, grandNode);
			}
		}
	}

	// Recoloring
	void recoloring(Node* _p, Node* _u, Node* _g)
	{
		if(_g != m_root) _g->setRB(true);
		_p->setRB(false);
		_u->setRB(false);
	}
	
	// Restructuring
	void restructuring(Node* _cur, Node* _p, Node* _g)
	{
		// u <= v < w
		Node* u = nullptr; Node* v = nullptr; Node* w = nullptr;

		if (*_cur < *_p)
		{
			if (*_cur < *_g)
			{
				u = _cur;
				if (*_g < *_p)
				{
					v = _g;
					w = _p;
				}
				else
				{
					v = _p;
					w = _g;
				}
			}
			else
			{
				u = _g;
				v = _cur;
				w = _p;
			}
		}
		else
		{
			if (*_p < *_g)
			{
				u = _p;
				if (*_g < *_cur)
				{
					v = _g;
					w = _cur;
				}
				else
				{
					v = _cur;
					w = _g;
				}
			}
			else
			{
				u = _g;
				v = _p;
				w = _cur;
			}
		}

		Node* subT1 = u->getLeft();
		Node* subT2; Node* subT3;
		if (v == _cur)
		{
			subT2 = _cur->getLeft();
			subT3 = _cur->getRight();
		}
		else
		{
			if (v->getPar()->getLeft() == v)
			{
				subT2 = u->getRight();
				subT3 = v->getRight();
			}
			else
			{
				subT2 = v->getLeft();
				subT3 = w->getLeft();
			}
		}
		Node* subT4 = w->getRight();

		
		if (_g->getPar() != nullptr)
		{
			if (_g->getPar()->getLeft() == _g)
			{
				_g->getPar()->setLeft(v);
			}
			else _g->getPar()->setRight(v);
		}
		v->setPar(_g->getPar());
		v->setLeft(u); v->setRight(w);
		v->setRB(false);
		if (_g == m_root)
			m_root = v;

		u->setPar(v);
		u->setLeft(subT1); u->setRight(subT2);
		if(subT1 != nullptr) subT1->setPar(u);
		if(subT2 != nullptr) subT2->setPar(u);
		u->setRB(true);

		w->setPar(v);
		w->setLeft(subT3); w->setRight(subT4);
		if (subT3 != nullptr) subT3->setPar(w);
		if (subT4 != nullptr) subT4->setPar(w);
		w->setRB(true);
	}

	void leftRotation(Node* _p)
	{
		Node* c = _p->getRight();
		_p->setRight(c);

		if (c->getLeft() != nullptr)
			c->getLeft()->setPar(_p);
		c->setPar(_p->getPar());

		if (_p->getPar() == nullptr)
			m_root = c;
		else if (_p == _p->getPar()->getLeft())
			_p->getPar()->setLeft(c);
		else
			_p->getPar()->setRight(c);

		c->setLeft(_p);
		_p->setPar(c);
	}

	void rightRotation(Node* _p)
	{
		Node* c = _p->getLeft();
		_p->setLeft(c);

		if (c->getRight() != nullptr)
			c->getRight()->setPar(_p);

		if (_p->getPar() == nullptr)
			m_root = c;
		else if (_p->getPar()->getLeft())
			_p->getPar()->setLeft(c);
		else
			_p->getPar()->setRight(c);

		c->setRight(_p);
		_p->setPar(c);
	}

	void transplant(Node* _del, Node* _repl)
	{
		if (_del->getPar() == nullptr)
			m_root = _repl;
		else if (_del->getPar()->getLeft() == _del)
			_del->getPar()->setLeft(_repl);
		else
			_del->getPar()->setRight(_repl);
		if(_repl != nullptr)
			_repl->setPar(_del->getPar());
	}

	Node* findMinOfSubtree(Node* _r)
	{
		if (_r->getLeft() != nullptr)
			findMinOfSubtree(_r->getLeft());
		else
			return _r;
	}
	public:
	void deleteNode(T _e)
	{
		Node* delNode = this->search(_e);
		if (delNode == nullptr) return;

		Node* rNode = delNode;
		Node* rrNode = nullptr;
		bool reNodeColor = rNode->getRB();

		// if the node(delNode) that will be deleted has just one child.
		if (delNode->getLeft() == nullptr)
		{
			rrNode = delNode->getRight();
			transplant(delNode, delNode->getRight());
		}
		else if (delNode->getRight() == nullptr)
		{
			rrNode = delNode->getLeft();
			transplant(delNode, delNode->getLeft());
		}
		// else = delNode has two child
		else
		{
			// find the node(rNode) that will replace the node which will be deleted.
			rNode = findMinOfSubtree(delNode->getRight());
			reNodeColor = rNode->getRB();
			rrNode = rNode->getRight();

			// if the rNode is the right child of delNode
			if (rNode->getPar() == delNode)
			{
				rrNode->setPar(rNode);
			}
			// else the rNode is not the right child of delNode
			else
			{
				transplant(rNode, rNode->getRight());
				rNode->setRight(delNode->getRight());
				rNode->getRight()->setPar(rNode);
			}

			// finish replacement
			transplant(delNode, rNode);
			rNode->setLeft(delNode->getLeft());
			rNode->getLeft()->setPar(rNode);
			rNode->setRB(delNode->getRB());

			// delete delNode
			// Since the destructor of node class deletes all children of the node, all children pointer of delNode must be set nullptr.
			delNode->setLeft(nullptr);
			delNode->setRight(nullptr);
			delete delNode;
		}

		if (reNodeColor == false)
			fixInDel(rrNode);
	}
	private:
	void fixInDel(Node* _rrNode)
	{
		while (_rrNode != m_root && !_rrNode->getRB())
		{
			if (_rrNode == _rrNode->getPar()->getLeft())
			{
				Node* sibling = _rrNode->getPar()->getRight();
				// case 1: the sibilng is red.
				if (sibling->getRB())
				{
					sibling->setRB(false);
					_rrNode->getPar()->setRB(true);
					leftRotation(_rrNode->getPar());
					sibling = _rrNode->getPar()->getRight();
				}
				// the sibling becomes or is black.
				// case 2: the two child of the sibling are black
				if ((!sibling->getLeft()->getRB() && !sibling->getRight()->getRB())
					|| (sibling->getLeft() == nullptr && sibling->getRight() == nullptr))
				{
					sibling->setRB(true);
					_rrNode = _rrNode->getPar();
				}
				else
				{
					// case 3: the right child of the sibling is black. And the left child of the sibling is red
					if (!sibling->getRight()->getRB() || sibling->getRight() == nullptr)
					{
						sibling->getLeft()->setRB(false);
						sibling->setRB(true);
						rightRotation(sibling);
						sibling = _rrNode->getPar()->getRight();
					}

					// in case 3, the right child of the sibling becomes black.
					// case 4: the right child of the sibing is red.
					sibling->setRB(_rrNode->getPar()->getRB());
					_rrNode->getPar()->setRB(false);
					if (sibling->getRight() != nullptr)
						sibling->getRight()->setRB(false);
					leftRotation(_rrNode->getPar());

					// when case 4 is fin, the probelm is solved. So, escape the loop.
					_rrNode = m_root;
				}
			}
			else
			{
				Node* sibling = _rrNode->getPar()->getLeft();
				// case 1: the sibilng is red.
				if (sibling->getRB())
				{
					sibling->setRB(false);
					_rrNode->getPar()->setRB(true);
					rightRotation(_rrNode->getPar());
					sibling = _rrNode->getPar()->getLeft();
				}
				// the sibling becomes or is black.
				// case 2: the two child of the sibling are black
				if ((!sibling->getLeft()->getRB() && !sibling->getRight()->getRB())
					|| (sibling->getLeft() == nullptr && sibling->getRight() == nullptr))
				{
					sibling->setRB(true);
					_rrNode = _rrNode->getPar();
				}
				else
				{
					// case 3: the right child of the sibling is black. And the left child of the sibling is red
					if (!sibling->getLeft()->getRB() || sibling->getLeft() == nullptr)
					{
						sibling->getRight()->setRB(false);
						sibling->setRB(true);
						leftRotation(sibling);
						sibling = _rrNode->getPar()->getLeft();
					}

					// in case 3, the right child of the sibling becomes black.
					// case 4: the right child of the sibing is red.
					sibling->setRB(_rrNode->getPar()->getRB());
					_rrNode->getPar()->setRB(false);
					if (sibling->getLeft() != nullptr)
						sibling->getLeft()->setRB(false);
					rightRotation(_rrNode->getPar());

					// when case 4 is fin, the probelm is solved. So, escape the loop.
					_rrNode = m_root;
				}
			}
		}
		_rrNode->setRB(false);
	}
	public:
	void checkPrintByInOrderTraversal(Node* _r)
	{
		if (_r->getLeft() != nullptr)
			checkPrintByInOrderTraversal(_r->getLeft());
		cout << _r->getElem() << '/' << (_r->getRB() ? "R" : "B") << '/' << _r->getDepth() << ' ';
		if (_r->getRight() != nullptr)
			checkPrintByInOrderTraversal(_r->getRight());
	}
};