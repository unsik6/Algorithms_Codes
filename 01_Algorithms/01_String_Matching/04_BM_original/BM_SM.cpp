#include "BM_SM.h"

#include <iostream>

using namespace std;


BM_SM::BM_SM()
{

}

BM_SM::~BM_SM()
{
	if (m_gsArr != nullptr)
	{
		delete[] m_gsArr;
	}
}

void BM_SM::constructBC(char* _pattern)
{
	for (int i = 0; i < m_patLength; i++)
		m_bcMap[_pattern[i]] = m_patLength - i - 1;
}

void BM_SM::constructBC(string _pattern)
{
	for (int i = 0; i < m_patLength; i++)
		m_bcMap[_pattern[i]] = m_patLength - i - 1;
}

void BM_SM::constructGS(char* _pattern)
{
	m_gsArr = new int[m_patLength];
	// reverse Z func: Z[i] is the length of suffix that equals substring which ends at string[i]
	int* revZfunc = new int[m_patLength];

	for (int i = 0; i < m_patLength - 1; i++)
	{
		revZfunc[i] = 0;
		m_gsArr[i] = -1;
	}
	m_gsArr[m_patLength - 1] = 1;

	int l, r;
	l = r = (int)m_patLength - 1;
	for (int i = (int)m_patLength - 2; i >= 0; i--)
	{
		if (i < l)
		{
			int j = (int)m_patLength - 1;
			while (m_patLength - 1 - j + (m_patLength - 1 - i) < m_patLength
				&& _pattern[j] == _pattern[i - (m_patLength - 1 - j)])
			{
				revZfunc[i]++;
				j--;
			}
		}
		else if (i - revZfunc[m_patLength - 1 - (r - i)] + 1 > l)
		{
			revZfunc[i] = revZfunc[m_patLength - 1 - (r - i)];
		}
		else
		{
			revZfunc[i] = i - l + 1;
			int j = l - 1;
			while (j >= 0 && _pattern[j] == _pattern[i - j])
			{
				revZfunc[i]++;
				r = i;
			}
		}

		if (i - revZfunc[i] + 1 < l)
		{
			l = i - revZfunc[i] + 1;
			r = i;
		}
	}

	// this dynamic array keep the position of the end of a suffix which is a prefix of pattern.
	vector<int> c2;
	// case 1: good suffix is the substring of pattern
	for (int i = 0; i < m_patLength - 1; i++)
	{
		if (revZfunc[i] > 0)
			m_gsArr[m_patLength - revZfunc[i] - 1] = i;
		if (i - revZfunc[i] + 1 == 0)
		{
			c2.push_back(i);
		}
	}

	// case 2: the suffix of good suffix is the prefix of pattern
	if (!c2.empty())	// if c2 vector is empty, then there is no case2.
	{
		c2.push_back((int)m_patLength);	// end point mark
		int c2VecPos = 0;
		for (int i = (int)m_patLength - 2; i >= 0; i--)
		{
			if (m_gsArr[i] == -1)
			{
				if (m_patLength - i - 1 < c2[c2VecPos] + 1)
					continue;

				while (m_patLength - i - 1 > c2[c2VecPos + 1] + 1)
				{
					c2VecPos++;
				}
				// There is no appropriate case2
				if (c2VecPos == -1)
					break;

				m_gsArr[i] = c2[c2VecPos];
			}
		}
	}

	for (int i = 0; i < (int)m_patLength - 1; i++)
	{
		m_gsArr[i] = (int)m_patLength * 2 - m_gsArr[i] - i - 2;
	}

	delete[] revZfunc;
}
void BM_SM::constructGS(string _pattern)
{
	m_gsArr = new int[m_patLength];
	// reverse Z func: Z[i] is the length of suffix that equals substring which ends at string[i]
	int* revZfunc = new int[m_patLength];

	for (int i = 0; i < m_patLength - 1; i++)
	{
		revZfunc[i] = 0;
		m_gsArr[i] = -1;
	}
	m_gsArr[m_patLength - 1] = 1;

	int l, r;
	l = r = (int)m_patLength - 1;
	for (int i = (int)m_patLength - 2; i >= 0; i--)
	{
		if (i < l)
		{
			int j = (int)m_patLength - 1;
			while (m_patLength - 1 - j + (m_patLength - 1 - i) < m_patLength
				&& _pattern[j] == _pattern[i - (m_patLength - 1 - j)])
			{
				revZfunc[i]++;
				j--;
			}
		}
		else if (i - revZfunc[m_patLength - 1 - (r - i)] + 1 > l)
		{
			revZfunc[i] = revZfunc[m_patLength - 1 - (r - i)];
		}
		else
		{
			revZfunc[i] = i - l + 1;
			int j = l - 1;
			while (j >= 0 && _pattern[j] == _pattern[i - j])
			{
				revZfunc[i]++;
				r = i;
			}
		}

		if (i - revZfunc[i] + 1 < l)
		{
			l = i - revZfunc[i] + 1;
			r = i;
		}
	}

	// this dynamic array keep the position of the end of a suffix which is a prefix of pattern.
	vector<int> c2;
	// case 1: good suffix is the substring of pattern
	for (int i = 0; i < m_patLength - 1; i++)
	{
		if(revZfunc[i] > 0)
			m_gsArr[m_patLength - revZfunc[i] - 1] = i;
		if (i - revZfunc[i] + 1 == 0)
		{
			c2.push_back(i);
		}
	}
	
	// case 2: the suffix of good suffix is the prefix of pattern
	if (!c2.empty())	// if c2 vector is empty, then there is no case2.
	{
		c2.push_back((int)m_patLength);	// end point mark
		int c2VecPos = 0;
		for (int i = (int)m_patLength - 2; i >= 0; i--)
		{
			if (m_gsArr[i] == -1)
			{
				if (m_patLength - i - 1 < c2[c2VecPos] + 1)
					continue;

				while(m_patLength - i - 1 > c2[c2VecPos + 1] + 1)
				{
					c2VecPos++;
				}
				// There is no appropriate case2
				if (c2VecPos == -1)
					break;

				m_gsArr[i] = c2[c2VecPos];
			}
		}
	}
	
	for (int i = 0; i < (int)m_patLength - 1; i++)
	{
		m_gsArr[i] = (int)m_patLength * 2 - m_gsArr[i] - i - 2;
	}

	delete[] revZfunc;
}

std::vector<int>* BM_SM::findAll_BM(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
{
	m_patLength = _patLength;
	constructBC(_pattern);
	constructGS(_pattern);

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

			i = i + (bcDistance >= m_gsArr[j] ? bcDistance : m_gsArr[j]);
			j = m_patLength - 1;
		}
	}

	return ret;
}
std::vector<int>* BM_SM::findAll_BM(string _text, string _pattern)
{
	m_patLength = _pattern.length();
	constructBC(_pattern);
	constructGS(_pattern);

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

			i = i + (bcDistance >= m_gsArr[j] ? bcDistance : m_gsArr[j]);
			j = m_patLength - 1;
		}
	}

	return ret;
}

void BM_SM::printResult(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
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
void BM_SM::printResult(string _text, string _pattern)
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

void BM_SM::printBC()
{
	cout << "Bad Character Table:\n";
	for (map<char, int>::iterator iter = m_bcMap.begin(); iter != m_bcMap.end(); iter++)
		cout << '(' << iter->first << ", " << iter->second << "), ";
	cout << '\n';
}
void BM_SM::printGS()
{
	cout << "Good Suffix Table\n";
	for (int i = 0; i < m_patLength; i++)
		cout << m_gsArr[i] << ' ';
	cout << '\n';
}