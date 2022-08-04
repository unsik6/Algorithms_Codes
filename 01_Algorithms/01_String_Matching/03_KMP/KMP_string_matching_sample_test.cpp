#include "KMP_SM.h"
using namespace std;

int main()
{
	int tL, pL;
	cout << "Text Length, Pattern Length: ";
	cin >> tL >> pL;
	char* cArr_text, *cArr_pattern;
	cArr_text = new char[tL];
	cArr_pattern = new char[pL];
	cout << "text: ";
	cin >> cArr_text;
	cout << "pattern: ";
	cin >> cArr_pattern;

	string strText = cArr_text;
	string strPattern = cArr_pattern;

	KMP_SM cTestKMP;
	KMP_SM strTestKMP;

	cout << "Char Array Test\n";
	cTestKMP.printResult(cArr_text, tL, cArr_pattern, pL);
	cTestKMP.printFailure();

	cout << "\nString Array Test\n";
	strTestKMP.printResult(strText, strPattern);
	strTestKMP.printFailure();
}