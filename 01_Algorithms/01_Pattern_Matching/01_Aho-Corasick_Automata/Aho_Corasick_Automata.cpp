#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include "AC_Automata.h"

using namespace std;

int main()
{
	vector<string> patArr;  string pat;
	cin >> pat;
	while (pat != "Q")
	{
		patArr.push_back(pat);
		cin >> pat;
	}
	AC_Automata testAutomaton(&patArr);
	testAutomaton.printForCheck();

	cout << endl << endl;

	string txt;
	cin >> txt;
	testAutomaton.patternMatching(txt);

	return 0;
}