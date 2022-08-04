#pragma once
#include <iostream>
#include <string>


/// <summary>
/// Rabin-Karp Algorithm.
/// It is configured to perform only the most basic form of the algorithm, and the inputable set of alphabets ¥Ò is limited to numbers between 0 and 9.
/// If we extend the function convert(char) to another ¥Ò, we will be able to deal with more strings.
/// </summary>
class Rabin_Karp {
private:
	int d; /// radix
	int q; /// modulus

	/// <summary>
	/// Verify that the s-shift of the text and pattern actually match.
	/// </summary>
	/// <param name="pattern">pattern</param>
	/// <param name="text">text</param>
	/// <param name="s">shift</param>
	/// <returns>Whether the s-shift of the text matches the pattern.</returns>
	bool equals(const std::string& pattern, const std::string& text, int s);

	/// <summary>
	/// The input character is converted to a corresponding number.
	/// </summary>
	/// <param name="c">character</param>
	/// <returns>The number corresponding to a character.</returns>
	const int convert(const char& c);
public:
	Rabin_Karp(int d = 10, int q = 13) : d(d), q(q) {
	}

	~Rabin_Karp() {
	}

	/// <summary>
	/// Pattern matching.
	/// </summary>
	/// <param name="pattern">pattern</param>
	/// <param name="text">text</param>
	void patternMatching(const std::string& pattern, const std::string& text);
};