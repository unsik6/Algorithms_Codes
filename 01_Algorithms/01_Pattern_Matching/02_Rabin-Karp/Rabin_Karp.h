#pragma once
#include <iostream>
#include <string>
using namespace std;


/// <summary>
/// Rabin-Karp 알고리즘을 수행한다.
/// 알고리즘의 가장 기본적인 형태만 수행하도록 구성되었으며, 입력 가능한 알파벳 집합 Σ은 0~9 사이의 숫자로 제한한다.
/// 만약, convert(char) 함수를 다른 Σ에 대하여 확장한다면 더 많은 문자열에 대하여 다룰 수 있을 것이다.
/// </summary>
class Rabin_Karp {
private:
	int d; /// 기수
	int q; /// 나누는 수

	/// <summary>
	/// 텍스트의 s-시프트와 패턴이 실제로 일치하는지 확인한다.
	/// </summary>
	/// <param name="pattern">패턴</param>
	/// <param name="text">텍스트</param>
	/// <param name="s">시프트</param>
	/// <returns>텍스트의 s-시프트와 패턴의 실제 일치 여부</returns>
	bool equals(const string& pattern, const string& text, int s);

	/// <summary>
	/// 입력된 문자를 대응하는 숫자로 변환한다.
	/// </summary>
	/// <param name="c">문자</param>
	/// <returns>문자에 대응하는 숫자</returns>
	const int convert(const char& c);
public:
	Rabin_Karp(int d = 10, int q = 13) : d(d), q(q) {
	}

	~Rabin_Karp() {
	}

	/// <summary>
	/// 패턴매칭을 실시한다.
	/// </summary>
	/// <param name="text">텍스트</param>
	void patternMatching(const string& pattern, const string& text);
};