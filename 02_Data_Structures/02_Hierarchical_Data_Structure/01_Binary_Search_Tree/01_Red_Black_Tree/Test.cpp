#include <iostream>
#include "RB_Tree.h"
using namespace std;

int main()
{
	RB_TREE<int> rb;
	string oper;
	cin >> oper;
	while (oper != "Q")
	{
		if (oper == "I")
		{
			int e;
			cin >> e;
			rb.insertNode(e);
		}
		else if (oper == "D")
		{
			int e;
			cin >> e;
			rb.deleteNode(e);
		}
		else if (oper == "S")
		{
			int e;
			cin >> e;
			cout << "Depth/Color: " << rb.search(e)->getDepth() << '/' << (rb.search(e)->getRB() ? "R" : "B") << '\n';
		}
		else if (oper == "P")
		{
			rb.checkPrintByInOrderTraversal(rb.getRoot());
			cout << '\n';
		}
		cin >> oper;
	}
}