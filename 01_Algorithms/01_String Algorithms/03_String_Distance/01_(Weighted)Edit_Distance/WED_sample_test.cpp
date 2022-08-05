#include "WED.h"

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

	int weights[4];
	cout << "Weights:\nINSERT: ";
	cin >> weights[0];
	cout << "DELETE: ";
	cin >> weights[1];
	cout << "REPLACE: ";
	cin >> weights[2];
	cout << "MATCHING: ";
	cin >> weights[3];

	string strText = cArr_text;
	string strPattern = cArr_pattern;

	WED cTestWED;
	WED strTestWED;

	cout << "Char Array Test\n";
	cTestWED.printResult(cArr_text, tL, cArr_pattern, pL, weights);

	cout << '\n';

	cout << "\nString Array Test\n";
	strTestWED.printResult(strText, strPattern, weights);
}