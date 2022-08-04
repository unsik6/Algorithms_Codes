#pragma once

#include <vector>
#include <map>
#include <string>

class BMH_SM
{
	std::map<char, int> m_bcMap;

	size_t m_patLength = 0;

public:
	BMH_SM();
	~BMH_SM();

private:
	void constructBC(char*);
	void constructBC(std::string);


public:
	std::vector<int>* findAll_BM(char*, size_t, char*, size_t);
	std::vector<int>* findAll_BM(std::string, std::string);

	void printResult(char*, size_t, char*, size_t);
	void printResult(std::string, std::string);

	void printBC();
};

