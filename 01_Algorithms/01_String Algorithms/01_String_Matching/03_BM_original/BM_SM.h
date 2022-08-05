#pragma once

#include <vector>
#include <map>
#include <string>

class BM_SM
{
	std::map<char, int> m_bcMap;
	int* m_gsArr = nullptr;

	size_t m_patLength = 0;

public:
	BM_SM();
	~BM_SM();

private:
	void constructBC(char*);
	void constructBC(std::string);

	void constructGS(char*);
	void constructGS(std::string);


public:
	std::vector<int>* findAll_BM(char*, size_t, char*, size_t);
	std::vector<int>* findAll_BM(std::string, std::string);

	void printResult(char*, size_t, char*, size_t);
	void printResult(std::string, std::string);

	void printBC();
	void printGS();
};

