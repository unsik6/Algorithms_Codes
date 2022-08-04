#pragma once

#include <string>
#include <vector>

class KMP_SM
{
private:
	int* m_failure;
	size_t m_patLength;

public:
	KMP_SM();
	~KMP_SM();

private:
	void constructFailure(char*);
	void constrcutFailure(std::string);

public:
	std::vector<int>* findAll_KMP(char*, size_t, char*, size_t);
	std::vector<int>* findAll_KMP(std::string, std::string);

	void printResult(char*, size_t, char*, size_t);
	void printResult(std::string, std::string);

	void printFailure();
};

