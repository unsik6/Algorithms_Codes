#include "LCS.h"

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

	LCS<int> cTestWED;
	LCS<int> strTestWED;

	cout << "Char Array Test\n";
	cTestWED.printResult(cArr_text, tL, cArr_pattern, pL);

	cout << '\n';

	cout << "\nString Array Test\n";
	strTestWED.printResult(strText, strPattern);
}