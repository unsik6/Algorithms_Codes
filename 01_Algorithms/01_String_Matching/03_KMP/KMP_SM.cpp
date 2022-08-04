#include "KMP_SM.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

KMP_SM::KMP_SM()
{
	m_failure = nullptr;
	m_patLength = 0;
}

KMP_SM::~KMP_SM()
{
	if (m_failure != nullptr)
		delete[] m_failure;
}

void KMP_SM::constructFailure(char* _pattern)
{
	m_failure = new int[m_patLength + 1];
	m_failure[0] = 0;
	int i = 1, j = 0;
	while(i < m_patLength)
	{
		if (_pattern[i] == _pattern[j])
		{
			m_failure[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0)
		{
			j = m_failure[j - 1];
		}
		else
		{
			m_failure[i] = 0;
			i++;
		}
	}
}
void KMP_SM::constrcutFailure(string _pattern)
{
	m_failure = new int[m_patLength + 1];
	m_failure[0] = 0;
	int i = 1, j = 0;
	while (i < m_patLength)
	{
		if (_pattern[i] == _pattern[j])
		{
			m_failure[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0)
		{
			j = m_failure[j - 1];
		}
		else
		{
			m_failure[i] = 0;
			i++;
		}
	}
}

vector<int>* KMP_SM::findAll_KMP(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
{
	m_patLength = _patLength;
	constrcutFailure(_pattern);

	if (m_failure == nullptr)
		cerr << "ERROR: Failure array not exist\n";

	vector<int>* ret = new vector<int>;

	int i = 0;
	int j = 0;
	while (i < _txtLength)
	{
		if (_text[i] == _pattern[j])
		{
			if (j == (int)_patLength - 1)
			{
				ret->push_back(i - j);
				i++;
				j = m_failure[j];
			}
			else
			{
				i++;
				j++;
			}
		}
		else if (j > 0)
		{
			j = m_failure[j - 1];
		}
		else
		{
			i++;
		}
	}

	return ret;
}
vector<int>* KMP_SM::findAll_KMP(string _text, string _pattern)
{
	m_patLength = _pattern.length();
	size_t txtLength = _text.length();
	constrcutFailure(_pattern);

	if (m_failure == nullptr)
		cerr << "ERROR: Failure array not exist\n";

	vector<int>* ret = new vector<int>;

	int i = 0;
	int j = 0;
	while (i < txtLength)
	{
		if (_text[i] == _pattern[j])
		{
			if (j == (int)m_patLength - 1)
			{
				ret->push_back(i - j);
				i++;
				j = m_failure[j];
			}
			else
			{
				i++;
				j++;
			}
		}
		else if (j > 0)
		{
			j = m_failure[j - 1];
		}
		else
		{
			i++;
		}
	}

	return ret;
}

void KMP_SM::printResult(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
{
	vector<int>* result = findAll_KMP(_text, _txtLength, _pattern, _patLength);

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
void KMP_SM::printResult(string _text, string _pattern)
{
	vector<int>* result = findAll_KMP(_text, _pattern);

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

void KMP_SM::printFailure()
{
	if(m_failure == nullptr)
		cerr << "ERROR: Failure array not exist\n";

	cout << "FAILURE : ";
	for (int i = 0; i < m_patLength; i++)
		cout << m_failure[i] << ' ';
	cout << '\n';
}