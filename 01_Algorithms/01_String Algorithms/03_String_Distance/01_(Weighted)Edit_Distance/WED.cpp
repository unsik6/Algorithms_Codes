#include "WED.h"
#include <iostream>

using namespace std;

WED::WED()
{
	m_dpMatrix = nullptr;
	m_dpPathMatrix = nullptr;
	for (int i = 0; i < 3; i++)
		m_weightMat[i] = 1;
	m_weightMat[WED_MAT] = 0;

	m_baseRow = 0;
	m_txtLength = m_patLength = 0;
}

WED::~WED()
{
	if (m_dpMatrix != nullptr)
	{
		if(m_dpMatrix[0] != nullptr)
			delete[] m_dpMatrix[0];
		if (m_dpMatrix[1] != nullptr)
			delete[] m_dpMatrix[1];
		delete[] m_dpMatrix;
	}
	if (m_dpPathMatrix != nullptr)
	{
		for (int i = 0; i < m_txtLength + 1; i++)
		{
			if(m_dpPathMatrix[i] != nullptr)
				delete[] m_dpPathMatrix[i];
		}
		delete[] m_dpPathMatrix;
	}
}

void WED::initializeMatrices(char* _text, size_t _txtLength, char* _pattern, size_t _patLength, int* _weights)
{
	// delete the information before used, and initialze members.
	if (m_dpMatrix != nullptr)
	{
		if (m_dpMatrix != nullptr)
		{
			if (m_dpMatrix[0] != nullptr)
				delete[] m_dpMatrix[0];
			if (m_dpMatrix[1] != nullptr)
				delete[] m_dpMatrix[1];
			delete[] m_dpMatrix;
		}
		if (m_dpPathMatrix != nullptr)
		{
			for (int i = 0; i < m_txtLength + 1; i++)
			{
				if (m_dpPathMatrix[i] != nullptr)
					delete[] m_dpPathMatrix[i];
			}
			delete[] m_dpPathMatrix;
		}

		m_dpMatrix = nullptr;
		m_dpPathMatrix = nullptr;
		for (int i = 0; i < 3; i++)
			m_weightMat[i] = 1;
		m_weightMat[WED_MAT] = 0;

		m_baseRow = 0;
		m_txtLength = m_patLength = 0;
	}

	m_txtLength = _txtLength;
	m_patLength = _patLength;
	m_dpMatrix = new int* [2];
	for (int i = 0; i < 2; i++)
		m_dpMatrix[i] = new int[m_patLength + 1];
	m_dpPathMatrix = new int* [m_txtLength + 1];
	for (int i = 0; i < m_txtLength + 1; i++)
		m_dpPathMatrix[i] = new int[m_patLength + 1];

	if (_weights != nullptr)
	{
		for (int i = 0; i < 4; i++)
			m_weightMat[i] = _weights[i];
	}
	// Not weighted Edit Distance
	else
	{
		for (int i = 0; i < 3; i++)
			m_weightMat[i] = 1;
		m_weightMat[WED_MAT] = 0;
	}
}
void WED::initializeMatrices(string _text, string _pattern, int* _weights)
{
	// delete the information before used, and initialze members.
	if (m_dpMatrix != nullptr)
	{
		if (m_dpMatrix != nullptr)
		{
			if (m_dpMatrix[0] != nullptr)
				delete[] m_dpMatrix[0];
			if (m_dpMatrix[1] != nullptr)
				delete[] m_dpMatrix[1];
			delete[] m_dpMatrix;
		}
		if (m_dpPathMatrix != nullptr)
		{
			for (int i = 0; i < m_txtLength + 1; i++)
			{
				if (m_dpPathMatrix[i] != nullptr)
					delete[] m_dpPathMatrix[i];
			}
			delete[] m_dpPathMatrix;
		}

		m_dpMatrix = nullptr;
		m_dpPathMatrix = nullptr;
		for (int i = 0; i < 3; i++)
			m_weightMat[i] = 1;
		m_weightMat[WED_MAT] = 0;

		m_baseRow = 0;
		m_txtLength = m_patLength = 0;
	}

	m_txtLength = _text.length();
	m_patLength = _pattern.length();
	m_dpMatrix = new int* [2];
	for (int i = 0; i < 2; i++)
		m_dpMatrix[i] = new int[m_patLength + 1];
	m_dpPathMatrix = new int* [m_txtLength + 1];
	for (int i = 0; i < m_txtLength + 1; i++)
		m_dpPathMatrix[i] = new int[m_patLength + 1];

	if (_weights != nullptr)
	{
		for (int i = 0; i < 4; i++)
			m_weightMat[i] = _weights[i];
	}
	// Not weighted Edit Distance
	else
	{
		for (int i = 0; i < 3; i++)
			m_weightMat[i] = 1;
		m_weightMat[WED_MAT] = 0;
	}
}

int WED::shortestDistance(char* _text, size_t _txtLength, char* _pattern, size_t _patLength, int* _weights)
{
	initializeMatrices(_text, _txtLength, _pattern, _patLength, _weights);

	int rowIdx = 1;

	m_dpMatrix[0][0] = 0;
	for (int c = 1; c < m_patLength + 1; c++)
	{
		m_dpMatrix[m_baseRow][c] = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_DEL];
		m_dpPathMatrix[m_baseRow][c] = WED_DEL;
	}

	int errorCnt = 0;
	while (rowIdx <= m_txtLength)
	{
		m_dpMatrix[(m_baseRow + 1) % 2][0] = m_dpMatrix[m_baseRow][0] + m_weightMat[WED_INS];
		m_dpPathMatrix[rowIdx][0] = WED_INS;

		for (int c = 1; c < m_patLength + 1; c++)
		{
			if (_text[rowIdx - 1] == _pattern[c - 1])
			{
				m_dpMatrix[(m_baseRow + 1) % 2][c] = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_MAT];
				m_dpPathMatrix[rowIdx][c] = WED_MAT;
			}
			else
			{
				// INSERT
				int minDistance = m_dpMatrix[m_baseRow][c] + m_weightMat[WED_INS];
				int minPath = WED_INS;

				// DELETE
				if (minDistance > m_dpMatrix[(m_baseRow + 1) % 2][c - 1] + m_weightMat[WED_DEL])
				{
					minDistance = m_dpMatrix[(m_baseRow + 1) % 2][c - 1] + m_weightMat[WED_DEL];
					minPath = WED_DEL;
				}

				// REPLACE
				if (minDistance > m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_REP])
				{
					minDistance = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_REP];
					minPath = WED_REP;
				}

				m_dpMatrix[(m_baseRow + 1) % 2][c] = minDistance;
				m_dpPathMatrix[rowIdx][c] = minPath;
			}
		}
		rowIdx++;
		errorCnt++;
		m_baseRow = (m_baseRow + 1) % 2;

		if (errorCnt > m_txtLength + 5)
		{
			cerr << "ERROR: INFINITE ITERATION\n";
			return -1;
		}
	}
	return m_dpMatrix[m_baseRow][m_patLength];
}
int WED::shortestDistance(string _text, string _pattern, int* _weights)
{
	initializeMatrices(_text, _pattern, _weights);

	int rowIdx = 1;

	m_dpMatrix[0][0] = 0;
	for (int c = 1; c < m_patLength + 1; c++)
	{
		m_dpMatrix[m_baseRow][c] = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_DEL];
		m_dpPathMatrix[m_baseRow][c] = WED_DEL;
	}

	int errorCnt = 0;
	while (rowIdx <= m_txtLength)
	{

		m_dpMatrix[(m_baseRow + 1) % 2][0] = m_dpMatrix[m_baseRow][0] + m_weightMat[WED_INS];
		m_dpPathMatrix[rowIdx][0] = WED_INS;

		for (int c = 1; c < m_patLength + 1; c++)
		{
			if (_text[rowIdx - 1] == _pattern[c - 1])
			{
				m_dpMatrix[(m_baseRow + 1) % 2][c] = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_MAT];
				m_dpPathMatrix[rowIdx][c] = WED_MAT;
			}
			else
			{
				// INSERT
				int minDistance = m_dpMatrix[m_baseRow][c] + m_weightMat[WED_INS];
				int minPath = WED_INS;

				// DELETE
				if (minDistance > m_dpMatrix[(m_baseRow + 1) % 2][c - 1] + m_weightMat[WED_DEL])
				{
					minDistance = m_dpMatrix[(m_baseRow + 1) % 2][c - 1] + m_weightMat[WED_DEL];
					minPath = WED_DEL;
				}

				// REPLACE
				if (minDistance > m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_REP])
				{
					minDistance = m_dpMatrix[m_baseRow][c - 1] + m_weightMat[WED_REP];
					minPath = WED_REP;
				}

				m_dpMatrix[(m_baseRow + 1) % 2][c] = minDistance;
				m_dpPathMatrix[rowIdx][c] = minPath;
			}
		}
		rowIdx++;
		errorCnt++;
		m_baseRow = (m_baseRow + 1) % 2;

		if (errorCnt > m_txtLength + 5)
		{
			cerr << "ERROR: INFINITE ITERATION\n";
			return -1;
		}
	}

	return m_dpMatrix[m_baseRow][m_patLength];
}

void WED::printRules()
{
	cout << "[Operation IDs] INSERT: " << WED_INS << ", DELETE: " << WED_DEL << ", REPLACE: " << WED_REP << ", MATCHING: " << WED_MAT
		<< "\n[Operation Weights] INSERT: " << m_weightMat[WED_INS] << ", DELETE: " << m_weightMat[WED_MAT] << ", REPLACE: " << m_weightMat[WED_REP] << ", MATCHING" << m_weightMat[WED_MAT] << endl;
}

vector<int>* WED::shortestPath(char* _text, size_t _txtLength, char* _pattern, size_t _patLength, int* _weights)
{
	shortestDistance(_text, _txtLength, _pattern, _patLength, _weights);
	vector<int>* path = new vector<int>;
	int rowIdx = (int)m_txtLength, colIdx = (int)m_patLength;
	while(rowIdx > 0 || colIdx > 0)
	{
		switch (m_dpPathMatrix[rowIdx][colIdx])
		{
		case WED_INS:
			rowIdx--;
			path->push_back(WED_INS);
			break;
		case WED_DEL:
			colIdx--;
			path->push_back(WED_DEL);
			break;
		case WED_REP:
			rowIdx--; colIdx--;
			path->push_back(WED_REP);
			break;
		case WED_MAT:
			rowIdx--; colIdx--;
			path->push_back(WED_MAT);
			break;
		}			
	}

	reverse(path->begin(), path->end());

	if (rowIdx == 0 && colIdx == 0)
		return path;
	else // ERROR
	{
		delete path;
		cerr << "ERROR: The table is constructed in wrong way\n";
	}
}

vector<int>* WED::shortestPath(string _text, string _pattern, int* _weights)
{
	shortestDistance(_text, _pattern, _weights);
	vector<int>* path = new vector<int>;
	int rowIdx = (int)m_txtLength, colIdx = (int)m_patLength;
	while (rowIdx > 0 || colIdx > 0)
	{
		switch (m_dpPathMatrix[rowIdx][colIdx])
		{
		case WED_INS:
			rowIdx--;
			path->push_back(WED_INS);
			break;
		case WED_DEL:
			colIdx--;
			path->push_back(WED_DEL);
			break;
		case WED_REP:
			rowIdx--; colIdx--;
			path->push_back(WED_REP);
			break;
		case WED_MAT:
			rowIdx--; colIdx--;
			path->push_back(WED_MAT);
			break;
		}
	}

	reverse(path->begin(), path->end());

	if (rowIdx == 0 && colIdx == 0)
		return path;
	else // ERROR
	{
		delete path;
		cerr << "ERROR: The table is constructed in wrong way\n";
	}
}
void WED::printResult(char* _text, size_t _txtLength, char* _pattern, size_t _patLength, int* _weights)
{
	cout << "***ALL RESULT***\n[Edit Distance]: " << shortestDistance(_text, _txtLength, _pattern, _patLength, _weights)
		<< "\n[Shortest Path] ";
	vector<int>* path = shortestPath(_text, _txtLength, _pattern, _patLength, _weights);
	vector<char> txt, pat;
	for (int i = 0; i < path->size(); i++)
	{
		switch (path->at(i))
		{
		case WED_INS:
			cout << 'I';
			break;
		case WED_DEL:
			cout << 'D';
			break;
		case WED_REP:
			cout << 'R';
			break;
		case WED_MAT:
			cout << 'M';
			break;
		default:
			cerr << "ERROR: There is a wrong operation.\n";
			return;
		}
		cout << ' ';
	}
	cout << "\n[Align text and pattern]\n";
	int txtIdx = 0, patIdx = 0;
	for (int i = 0; i < path->size(); i++)
	{
		switch (path->at(i))
		{
		case WED_INS:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(' ');
			break;
		case WED_DEL:
			txt.push_back(' ');
			pat.push_back(_pattern[patIdx++]);
			break;
		case WED_REP:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(_pattern[patIdx++]);
			break;
		case WED_MAT:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(_pattern[patIdx++]);
			break;
		default:
			cerr << "ERROR: There is a wrong operation.\n";
			return;
		}

		if (txtIdx > m_txtLength || patIdx > m_patLength)
		{
			cerr << "ERROR: OUT of Range of vector in print\n";
			return;
		}
	}
	for (int i = 0; i < pat.size(); i++)
		cout << pat[i] << ' ';
	cout << '\n';
	for (int i = 0; i < txt.size(); i++)
		cout << txt[i] << ' ';
	cout << '\n';

	cout << "\n[Distance DP Matrix]\n";
	for (int i = 1; i < 3; i++)
	{
		cout << m_txtLength - (i % 2) << "row: ";
		for (int c = 0; c < m_patLength + 1; c++)
			cout << m_dpMatrix[(m_baseRow + i) % 2][c] << ' ';
		cout << '\n';
	}
	cout << "\n[Path DP Matrix]\n  \' \'";
	// for look
	m_dpPathMatrix[0][0] = 0;
	for (int j = 0; j < m_patLength; j++)
		cout << _pattern[j] << ' ';
	cout << '\n';
	for (int i = 0; i < m_txtLength + 1; i++)
	{
		if (i == 0) cout << " : ";
		else cout << _text[i - 1] << ": ";
		for (int c = 0; c < m_patLength + 1; c++)
			cout << m_dpPathMatrix[i][c] << ' ';
		cout << '\n';
	}
	
	delete path;
}
void WED::printResult(string _text, string _pattern, int* _weights)
{
	cout << "***ALL RESULT***\n[Edit Distance]: " << shortestDistance(_text, _pattern, _weights)
		<< "\n[Shortest Path] ";
	vector<int>* path = shortestPath(_text, _pattern, _weights);
	vector<char> txt, pat;
	for (int i = 0; i < path->size(); i++)
	{
		switch (path->at(i))
		{
		case WED_INS:
			cout << 'I';
			break;
		case WED_DEL:
			cout << 'D';
			break;
		case WED_REP:
			cout << 'R';
			break;
		case WED_MAT:
			cout << 'M';
			break;
		default:
			cerr << "ERROR: There is a wrong operation.\n";
			return;
		}
		cout << ' ';
	}
	cout << "\n[Align text and pattern]\n";
	int txtIdx = 0, patIdx = 0;
	for (int i = 0; i < path->size(); i++)
	{
		switch (path->at(i))
		{
		case WED_INS:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(' ');
			break;
		case WED_DEL:
			txt.push_back(' ');
			pat.push_back(_pattern[patIdx++]);
			break;
		case WED_REP:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(_pattern[patIdx++]);
			break;
		case WED_MAT:
			txt.push_back(_text[txtIdx++]);
			pat.push_back(_pattern[patIdx++]);
			break;
		default:
			cerr << "ERROR: There is a wrong operation.\n";
			return;
		}

		if (txtIdx > m_txtLength || patIdx > m_patLength)
		{
			cerr << "ERROR: OUT of Range of vector in print\n";
			return;
		}
	}
	for (int i = 0; i < pat.size(); i++)
		cout << pat[i] << ' ';
	cout << '\n';
	for (int i = 0; i < txt.size(); i++)
		cout << txt[i] << ' ';
	cout << '\n';

	cout << "\n[Distance DP Matrix]\n";
	for (int i = 1; i < 3; i++)
	{
		cout << m_txtLength - (i % 2) << "row: ";
		for (int c = 0; c < m_patLength + 1; c++)
			cout << m_dpMatrix[(m_baseRow + i) % 2][c] << ' ';
		cout << '\n';
	}

	cout << "\n[Path DP Matrix]\n  \' \'";
	// for look
	m_dpPathMatrix[0][0] = 0;
	for (int j = 0; j < m_patLength; j++)
		cout << _pattern[j] << ' ';
	cout << '\n';
	for (int i = 0; i < m_txtLength + 1; i++)
	{
		if (i == 0) cout << " : ";
		else cout << _text[i - 1] << ": ";
		for (int c = 0; c < m_patLength + 1; c++)
			cout << m_dpPathMatrix[i][c] << ' ';
		cout << '\n';
	}

	delete path;
}