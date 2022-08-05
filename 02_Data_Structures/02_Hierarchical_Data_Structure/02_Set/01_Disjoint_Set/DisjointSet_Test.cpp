#include <iostream>
#include "Heap.h"
#include "DisjointSet.h"
using namespace std;

int main()
{
	int N;
	cin >> N;
	int* testArr = new int[N];
	for (int i = 0; i < N; i++)
		cin >> testArr[i];

	DisjointSet<int> disJoint(testArr, N);
	disJoint.print();
	cout << '\n';
	disJoint.unionSets(1, 2);
	disJoint.print();
	cout << '\n';
	disJoint.unionSets(2, 3);
	disJoint.print();
	cout << '\n';
	cout << disJoint.find(1);
	cout << '\n';
}