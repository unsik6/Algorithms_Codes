#pragma once

#include <string>
#include <vector>

#define WED_INS 0
#define WED_DEL 1
#define WED_REP 2
#define WED_MAT 3


class WED
{
	int** m_dpMatrix;
	int** m_dpPathMatrix;

	int m_weightMat[4];
	int m_baseRow;

	size_t m_txtLength, m_patLength;

public:
	WED();
	~WED();

private:
	void initializeMatrices(char*, size_t, char*, size_t, int* = nullptr);
	void initializeMatrices(std::string, std::string, int* = nullptr);

public:
	int shortestDistance(char*, size_t, char*, size_t, int* = nullptr);
	int shortestDistance(std::string, std::string, int* = nullptr);

	void printRules();
	std::vector<int>* shortestPath(char*, size_t, char*, size_t, int* = nullptr);
	std::vector<int>* shortestPath(std::string, std::string, int* = nullptr);

	void printResult(char*, size_t, char*, size_t, int* = nullptr);
	void printResult(std::string, std::string, int* = nullptr);
};

