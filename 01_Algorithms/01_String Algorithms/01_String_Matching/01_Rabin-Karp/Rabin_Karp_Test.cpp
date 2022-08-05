#include <iostream>
#include "Rabin_Karp.h"
using namespace std;


int main() {
	int t;
	cin >> t;

	Rabin_Karp rk = Rabin_Karp();

	for (int i = 0; i < t; i++) {
		string pattern, text;
		cin >> pattern >> text;
		rk.patternMatching(pattern, text);
	}
}