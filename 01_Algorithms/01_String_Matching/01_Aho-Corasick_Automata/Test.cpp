#include <iostream>
#include "AC_Automata.h"

using namespace std;




int main()
{
	vector<string> patterns;
	string curPat;
	cin >> curPat;
	while (curPat != "Q")
	{
		patterns.push_back(curPat);
		cin >> curPat;
	}

	AC_Automata ac(&patterns);
	string text;
	cin >> text;

	ac.printForCheck();
	cout << endl;
	ac.patternMatching(text);
}
