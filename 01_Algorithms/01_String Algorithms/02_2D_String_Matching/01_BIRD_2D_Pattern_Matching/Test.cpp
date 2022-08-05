#include <iostream>
#include "BIRD_2D.h"

using namespace std;




int main()
{
	int n, m;
	cin >> n >> m;
	string* text = new string[n];
	string* pattern = new string[m];
	
	for (int i = 0; i < n; i++)
		cin >> text[i];
	for (int i = 0; i < m; i++)
		cin >> pattern[i];

	BIRD_2D bird(text, n, pattern, m);
	bird.patternMatching();

	return 0;
}
