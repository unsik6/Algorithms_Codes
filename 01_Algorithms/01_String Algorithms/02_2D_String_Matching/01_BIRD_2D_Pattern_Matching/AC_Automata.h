#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>

class AC_Automata
{
protected:
	struct edgePair
	{
		int symbol;
		int dstState;
	};

	std::vector<std::list<edgePair*>*> m_automaton;
	std::vector<std::vector<int>*> m_outputs;	// ouputs[state] = pattern rows
	int* m_failure;

	int m_patternNum = 0;
	std::string* m_patterns;	// This string array is only for restoring patterns.

public:
	AC_Automata()
	{
		m_automaton.push_back(new std::list<edgePair*>);
		m_outputs.push_back(new std::vector<int>);
		m_patterns = nullptr;
		m_failure = nullptr;
	}
	AC_Automata(std::vector<std::string>* _patArr) : AC_Automata()
	{
		construct(_patArr);
	}
	~AC_Automata()
	{
		for (int i = 0; i < m_automaton.size(); i++)
		{
			delete m_automaton[i];
			delete m_outputs[i];
		}
		delete[] m_failure;
		delete[] m_patterns;
	}

	// gotoFunc(state, symbol)
	// go to the node of the edge labeled symbol from state.
	int gotoFunc(int, int);

	// construct(pattern strings)
	// construct Automata, Failure Array(Func), OutputArray(Func)
	void construct(std::vector<std::string>*);

	// patternMatching(text)
	// Find all location of all patterns that occurs in text
	void patternMatching(std::string);

	// Check all datastructre to check the AC automata is build correctly
	void printForCheck();

	std::vector<std::vector<int>*>* getOutputs() { return &m_outputs; }
	int failureFunc(int _state) { return m_failure[_state]; }
};