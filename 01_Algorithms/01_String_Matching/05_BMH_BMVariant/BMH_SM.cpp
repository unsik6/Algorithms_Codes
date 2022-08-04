#include "BMH_SM.h"

#include <iostream>

using namespace std;


BMH_SM::BMH_SM()
{

}

BMH_SM::~BMH_SM()
{

}

void BMH_SM::constructBC(char* _pattern)
{
	for (int i = 0; i < m_patLength; i++)
		m_bcMap[_pattern[i]] = m_patLength - i - 1;
}

void BMH_SM::constructBC(string _pattern)
{
	for (int i = 0; i < m_patLength; i++)
		m_bcMap[_pattern[i]] = m_patLength - i - 1;
}


std::vector<int>* BMH_SM::findAll_BM(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
{
	m_patLength = _patLength;
	constructBC(_pattern);

	vector<int>* ret = new vector<int>;

	int i = m_patLength - 1;
	int j = m_patLength - 1;
	while (i < _txtLength)
	{
		if (_text[i] == _pattern[j])
		{
			if (j == 0)
			{
				ret->push_back(i);
				i = i + m_patLength;
				j = m_patLength - 1;
			}
			else
			{
				i--; j--;
			}
		}
		else
		{
			int bcDistance;
			if (m_bcMap.find(_text[i]) == m_bcMap.end())
				bcDistance = m_patLength;
			else bcDistance = m_bcMap[_text[i]];

			
			i = i + (bcDistance >= m_patLength - j ? bcDistance : m_patLength - j);
			j = m_patLength - 1;
		}
	}

	return ret;
}
std::vector<int>* BMH_SM::findAll_BM(string _text, string _pattern)
{
	m_patLength = _pattern.length();
	constructBC(_pattern);

	vector<int>* ret = new vector<int>;

	int i = m_patLength - 1;
	int j = m_patLength - 1;
	while (i < _text.length())
	{
		if (_text[i] == _pattern[j])
		{
			if (j == 0)
			{
				ret->push_back(i);
				i = i + m_patLength;
				j = m_patLength - 1;
			}
			else
			{
				i--; j--;
			}
		}
		else
		{
			int bcDistance;
			if (m_bcMap.find(_text[i]) == m_bcMap.end())
				bcDistance = m_patLength;
			else bcDistance = m_bcMap[_text[i]];

			i = i + (bcDistance >= m_patLength - j ? bcDistance : m_patLength - j);
			j = m_patLength - 1;
		}
	}

	return ret;
}

void BMH_SM::printResult(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
{
	vector<int>* result = findAll_BM(_text, _txtLength, _pattern, _patLength);

	cout << "Pattern occurrence : ";
	if (result->empty())
		cout << "No occurrence\n";
	else
	{
		for (int i = 0; i < result->size(); i++)
			cout << result->at(i) << ' ';
		cout << '\n';
	}

	delete result;
}
void BMH_SM::printResult(string _text, string _pattern)
{
	vector<int>* result = findAll_BM(_text, _pattern);

	cout << "Pattern occurrence : ";
	if (result->empty())
		cout << "No occurrence\n";
	else
	{
		for (int i = 0; i < result->size(); i++)
			cout << result->at(i) << ' ';
		cout << '\n';
	}

	delete result;
}

void BMH_SM::printBC()
{
	cout << "Bad Character Table:\n";
	for (map<char, int>::iterator iter = m_bcMap.begin(); iter != m_bcMap.end(); iter++)
		cout << '(' << iter->first << ", " << iter->second << "), ";
	cout << '\n';
}