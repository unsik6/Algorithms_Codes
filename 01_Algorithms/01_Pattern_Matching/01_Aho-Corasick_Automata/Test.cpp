#include <iostream>
#include "C:\Users\ShinHyeonJun\Desktop\Test\Test\BIRD_2D.h"

using namespace std;




int main()
{
	int N, M;
	cin >> N >> M;
	string* txtRow = new string[N];
	for (int i = 0; i < N; i++)
	{
		cin >> txtRow[i];
	}
	string* patRow = new string[M];
	for (int i = 0; i < M; i++)
	{
		cin >> patRow[i];
	}

	BIRD_2D bird(txtRow, N, patRow, M);
	bird.checkPrint();
	bird.patternMatching();

	return 0;
}