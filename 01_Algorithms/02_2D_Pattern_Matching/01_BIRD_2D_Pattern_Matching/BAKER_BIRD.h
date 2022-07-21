#pragma once
#include "AC_Automata.h"

class BAKER_BIRD
{
	int m_txtSize = 0; int m_patSize = 0;
	string* m_txt = nullptr;
	string* m_pats = nullptr;

	AC_Automata* m_ac = nullptr;
	int* m_arrLabelOfPatRow = nullptr;
	int* m_kmpFArray = nullptr;

public:
	BAKER_BIRD(string* _txt, int _tSize, string* _pat, int _pSize)
	{
		m_txt = _txt;
		m_pats = _pat;
		m_txtSize = _tSize;
		m_patSize = _pSize;
		m_kmpFArray = new int[m_patSize];
		m_arrLabelOfPatRow = new int[m_patSize];
		
		constructAC();
		labelingPatternRow();
		constructKMPFailure();
	}
	~BAKER_BIRD()
	{
		delete[] m_kmpFArray;
		delete[] m_arrLabelOfPatRow;
		delete m_ac;
	}

	// Construct AC automata for row matching
	// using AC_Automata Class implemented by unsik6
	void constructAC();

	// Label the rows of pattern.
	// if the row is same with any previous, then the row is labeled the number labeled to the previous row.
	// else the row is laebeled with new number.
	void labelingPatternRow();
	
	// Construct the failure func about the rows of pattern, using KMP
	// We will use this in column matching
	void constructKMPFailure();

	// Return whether the row is one of the output of the state.
	bool isTerminal(int, int);

	void patternMatching();

	void checkPrint();



};