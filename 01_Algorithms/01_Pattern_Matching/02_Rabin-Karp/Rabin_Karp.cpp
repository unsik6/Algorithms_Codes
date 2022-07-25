#include "Rabin_Karp.h"
using namespace std;


bool Rabin_Karp::equals(const string& pattern, const string& text, int s) {
	for (int i = 0; i < pattern.length(); i++) {
		if (pattern[i] != text[s + i])
			return false;
	}
	return true;
}

const int Rabin_Karp::convert(const char& c) {
	return c - '0';
}

void Rabin_Karp::patternMatching(const string& pattern, const string& text) {
	int h = 1; /// 점화식 연산의 가중치
	for (int i = 0; i < pattern.length() - 1; i++)
		h *= d;
	h = h % q;

	int p = 0; /// 패턴에 대응하는 숫자
	int t = 0; /// 텍스트의 현재 시프트에 대응하는 숫자
	for (int i = 0; i < pattern.length(); i++) {
		p = (d * p + convert(pattern[i])) % q;
		t = (d * t + convert(text[i])) % q;
	}

	for (int s = 0; s <= text.length() - pattern.length(); s++) {
		if (p == t) {
			if (equals(pattern, text, s))
				cout << s << " ";
		}
		if (s < text.length() - pattern.length()) {
			t = (d * (t - convert(text[s]) * h) + convert(text[s + pattern.length()])) % q;
			t = (t + q) % q;
		}
	}
	cout << endl;
}