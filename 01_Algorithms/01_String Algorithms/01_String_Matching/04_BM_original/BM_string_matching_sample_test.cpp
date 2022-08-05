#include <iostream>
#include "BM_SM.h"

using namespace std;




int main()
{
	int tL, pL;
	cout << "Text Length, Pattern Length: ";
	cin >> tL >> pL;
	char* cArr_text, * cArr_pattern;
	cArr_text = new char[tL];
	cArr_pattern = new char[pL];
	cout << "text: ";
	cin >> cArr_text;
	cout << "pattern: ";
	cin >> cArr_pattern;

	string strText = cArr_text;
	string strPattern = cArr_pattern;

	BM_SM cTestBM;
	BM_SM strTestBM;

	cout << "Char Array Test\n";
	cTestBM.printResult(cArr_text, tL, cArr_pattern, pL);
	cTestBM.printBC();
	cTestBM.printGS();

	cout << '\n';

	cout << "\nString Array Test\n";
	strTestBM.printResult(strText, strPattern);
	strTestBM.printBC();
	strTestBM.printGS();
}