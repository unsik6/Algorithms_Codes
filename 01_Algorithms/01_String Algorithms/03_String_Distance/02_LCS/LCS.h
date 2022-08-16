#pragma once
#include <iostream>

// T is a numeric type.
template<typename T>
class LCS
{
	enum class FLAG { MATCHING, LEFT, UP };

	T** m_lcsMatrix;
	FLAG** m_flagMatrix;

	size_t m_txtLength, m_patLength;

public:
	LCS()
	{
		m_lcsMatrix = nullptr;
		m_flagMatrix = nullptr;
		m_txtLength = m_patLength = 0;
	}

	~LCS()
	{
		if (m_lcsMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_lcsMatrix[r];
			}
			delete[] m_lcsMatrix;
		}
		if (m_flagMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_flagMatrix[r];
			}
			delete[] m_flagMatrix;
		}
	}

	T LCSLength(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
	{
		// initiate Matrix
		if (m_lcsMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_lcsMatrix[r];
			}
			delete[] m_lcsMatrix;
		}
		if (m_flagMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_flagMatrix[r];
			}
			delete[] m_flagMatrix;
		}

		m_txtLength = _txtLength;
		m_patLength = _patLength;

		// preprocessing
		m_lcsMatrix = new T * [m_txtLength + 1];
		m_flagMatrix = new FLAG * [m_txtLength + 1];
		for (int i = 0; i <= m_txtLength; i++)
		{
			m_lcsMatrix[i] = new T[m_patLength + 1];
			m_lcsMatrix[i][0] = 0;

			m_flagMatrix[i] = new FLAG[m_patLength + 1];
			m_flagMatrix[i][0] = FLAG::UP;
		}
		for (int c = 1; c <= m_patLength; c++)
		{
			m_lcsMatrix[0][c] = 0;
			m_flagMatrix[0][c] = FLAG::LEFT;
		}

		// compute LCS length
		for (int r = 1; r <= m_txtLength; r++)
		{
			for (int c = 1; c <= m_patLength; c++)
			{
				if (_text[r - 1] == _pattern[c - 1])
				{
					m_lcsMatrix[r][c] = m_lcsMatrix[r - 1][c - 1] + 1;
					m_flagMatrix[r][c] = FLAG::MATCHING;
				}
				else
				{
					T max = m_lcsMatrix[r - 1][c];
					if (max < m_lcsMatrix[r][c - 1])
					{
						max = m_lcsMatrix[r][c - 1];
						m_flagMatrix[r][c] = FLAG::LEFT;
					}
					else
					{
						m_flagMatrix[r][c] = FLAG::UP;
					}

					m_lcsMatrix[r][c] = max;
				}
			}
		}

		return m_lcsMatrix[m_txtLength][m_patLength];
	}

	T LCSLength(std::string _text, std::string _pattern)
	{
		// initiate Matrix
		if (m_lcsMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_lcsMatrix[r];
			}
			delete[] m_lcsMatrix;
		}
		if (m_flagMatrix != nullptr)
		{
			for (int r = 0; r <= m_txtLength; r++)
			{
				delete[] m_flagMatrix[r];
			}
			delete[] m_flagMatrix;
		}

		m_txtLength = _text.length();
		m_patLength = _pattern.length();

		// preprocessing
		m_lcsMatrix = new T * [m_txtLength + 1];
		m_flagMatrix = new FLAG * [m_txtLength + 1];
		for (int i = 0; i <= m_txtLength; i++)
		{
			m_lcsMatrix[i] = new T[m_patLength + 1];
			m_lcsMatrix[i][0] = 0;

			m_flagMatrix[i] = new FLAG[m_patLength + 1];
			m_flagMatrix[i][0] = FLAG::UP;
		}
		for (int c = 1; c <= m_patLength; c++)
		{
			m_lcsMatrix[0][c] = 0;
			m_flagMatrix[0][c] = FLAG::LEFT;
		}

		// compute LCS length
		for (int r = 1; r <= m_txtLength; r++)
		{
			for (int c = 1; c <= m_patLength; c++)
			{
				if (_text[r - 1] == _pattern[c - 1])
				{
					m_lcsMatrix[r][c] = m_lcsMatrix[r - 1][c - 1] + 1;
					m_flagMatrix[r][c] = FLAG::MATCHING;
				}
				else
				{
					T max = m_lcsMatrix[r - 1][c];
					if (max < m_lcsMatrix[r][c - 1])
					{
						max = m_lcsMatrix[r][c - 1];
						m_flagMatrix[r][c] = FLAG::LEFT;
					}
					else
					{
						m_flagMatrix[r][c] = FLAG::UP;
					}

					m_lcsMatrix[r][c] = max;
				}
			}
		}

		return m_lcsMatrix[m_txtLength][m_patLength];
	}

	char* cstringLCS(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
	{
		T lcsLength = LCSLength(_text, _txtLength, _pattern, _patLength);
		char* lcs = new char[lcsLength + 1];
		lcs[lcsLength] = '\0';
		T idx = lcsLength - 1;

		T r = m_txtLength, c = m_patLength;

		while (!(r == 0 && c == 0))
		{
			switch (m_flagMatrix[r][c])
			{
			case FLAG::MATCHING:
				lcs[idx--] = _text[r - 1];
				r--; c--;
				break;
			case FLAG::UP:
				r--;
				break;
			case FLAG::LEFT:
				c--;
				break;
			default:
				std::cerr << "ERROR: INCORRECT FLAG\n";
				break;
			}
		}

		if (idx != -1)
		{
			std::cerr << "ERROR: CONSTRUCT LCS FAIL\n";
		}

		return lcs;
	}

	char* cstringLCS(std::string _text, std::string _pattern)
	{
		T lcsLength = LCSLength(_text, _pattern);
		char* lcs = new char[lcsLength + 1];
		lcs[lcsLength] = '\0';
		T idx = lcsLength - 1;
		
		
		T r = m_txtLength, c = m_patLength;

		while (!(r == 0 && c == 0))
		{
			switch (m_flagMatrix[r][c])
			{
			case FLAG::MATCHING:
				lcs[idx--] = _text[r - 1];
				r--; c--;
				break;
			case FLAG::UP:
				r--;
				break;
			case FLAG::LEFT:
				c--;
				break;
			default:
				std::cerr << "ERROR: INCORRECT FLAG\n";
				break;
			}
		}

		if (idx != -1)
		{
			std::cerr << "ERROR: CONSTRUCT LCS FAIL\n";
		}

		return lcs;
	}

	void printCheck()
	{
		std::cout << "LCS_Matrix:\n";
		for (int i = 0; i <= m_txtLength; i++)
		{
			for (int j = 0; j <= m_patLength; j++)
			{
				std::cout << m_lcsMatrix[i][j] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "FLAG_Matrix:\n";
		for (int i = 0; i <= m_txtLength; i++)
		{
			for (int j = 0; j <= m_patLength; j++)
			{
				std::cout << (int)m_flagMatrix[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}

	void printResult(std::string _text, std::string _pattern)
	{
		T lcsLength = LCSLength(_text, _pattern);
		printCheck();
		char* lcs = cstringLCS(_text, _pattern);
		std::cout << "* LCS Length : " << lcsLength << "\n* LCS: " << lcs;

		delete[] lcs;
	}

	void printResult(char* _text, size_t _txtLength, char* _pattern, size_t _patLength)
	{
		T lcsLength = LCSLength(_text, _txtLength, _pattern, _patLength);
		printCheck();
		char* lcs = cstringLCS(_text, _txtLength, _pattern, _patLength);
		std::cout << "* LCS Length : " << lcsLength << "\n* LCS: " << lcs;

		delete[] lcs;
	}
};

