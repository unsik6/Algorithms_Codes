#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
using namespace std;

#pragma once
class AC_Automata
{
	struct edgePair
	{
		int symbol;
		int dstState;
	};

	vector<list<edgePair*>*> m_automaton;
	vector<vector<int>*> m_outputs;	// ouputs[state] = pattern rows
	int* m_failure;

	int patternNum = 0;
	string* patterns;	// This string array is only for restoring patterns.

public:
	AC_Automata()
	{
		m_automaton.push_back(new list<edgePair*>);
		m_outputs.push_back(new vector<int>);
		patterns = nullptr;
		m_failure = nullptr;
	}
	AC_Automata(vector<string>* _patArr) : AC_Automata()
	{
		construct(_patArr);
	}
	~AC_Automata()
	{
		for (int i = 0; i < m_automaton.size(); i++)
			delete m_automaton[i];
	}

	// gotoFunc(state, symbol)
	// go to the node of the edge labeled symbol from state.
	int gotoFunc(int, int);

	// construct(pattern strings)
	// construct Automata, Failure Array(Func), OutputArray(Func)
	void construct(vector<string>*);

	// patternMatching(text)
	// Find all location of all patterns that occurs in text
	void patternMatching(string);

	// Check all datastructre to check the AC automata is build correctly
	void printForCheck();
};

