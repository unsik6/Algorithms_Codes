#include "BAKER_BIRD.h"

void BAKER_BIRD::labelingPatternRow()
{
	vector<vector<int>*>* outputsPtr = m_ac->getOutputs();
	for (int i = 0; i < outputsPtr->size(); i++)
	{
		if (!outputsPtr->at(i)->empty())
		{
			int firstRowNum = outputsPtr->at(i)->at(0);
			m_arrLabelOfPatRow[firstRowNum] = firstRowNum;
			for (int j = 1; j < outputsPtr->at(i)->size(); j++)
			{
				m_arrLabelOfPatRow[outputsPtr->at(i)->at(j)] = firstRowNum;
			}
		}
	}
}

void BAKER_BIRD::constructAC()
{
	// change string array to string vector
	vector<string> tmpPats;
	for (int i = 0; i < m_patSize; i++)
	{
		tmpPats.push_back(m_pats[i]);
	}

	// constructAC
	m_ac = new AC_Automata(&tmpPats);
}

void BAKER_BIRD::constructKMPFailure()
{
	m_kmpFArray[0] = -1;
	int i = 1, j = 0;
	while (i < m_patSize)
	{
		if (m_arrLabelOfPatRow[i] == m_arrLabelOfPatRow[j])
		{
			m_kmpFArray[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0)
		{
			j = m_kmpFArray[j - 1];
		}
		else
		{
			m_kmpFArray[i] = 0;
			i++;
		}
	}
}

bool BAKER_BIRD::isTerminal(int _state, int _rowLabel)
{
	vector<vector<int>*>* outputsPtr = m_ac->getOutputs();
	for (int i = 0; i < outputsPtr->at(_state)->size(); i++)
	{
		if (outputsPtr->at(_state)->at(i) == _rowLabel)
			return true;
	}
	return false;
}

void BAKER_BIRD::patternMatching()
{
	cout << "pattern Matching";
	vector<vector<int>*>* outputsPtr = m_ac->getOutputs();
	int* kmpVector = new int[m_txtSize] {0};
	for (int i = 0; i < m_txtSize; i++)
	{
		int curState = 0;
		// row matching
		for (int k = 0; k < m_txtSize; k++)
		{
			while (m_ac->gotoFunc(curState, m_txt[i][k]) == -1)
				curState = m_ac->failureFunc(curState);
			curState = m_ac->gotoFunc(curState, m_txt[i][k]);
			
			if (!outputsPtr->at(curState)->empty())
			{
				int checkKMP = kmpVector[k];
				while (checkKMP >= 0 && !isTerminal(curState, checkKMP))
				{
					checkKMP = m_kmpFArray[checkKMP];
				}
				kmpVector[k] = checkKMP + 1;
				
				if (checkKMP == m_patSize - 1)
				{
					cout << "( " << i << ", " << k << " ),";
					kmpVector[k] = m_kmpFArray[m_patSize - 1];
				}
			}
			else
			{
				kmpVector[k] = 0;
			}
		}
		cout << '\n';
	}

	cout << '\n';
}

void BAKER_BIRD::checkPrint()
{
	m_ac->printForCheck();
	cout << "\n---------------\nLabels of each row of the pattern\n";
	for (int i = 0; i < m_patSize; i++)
	{
		cout << m_arrLabelOfPatRow[i] << ' ';
	}

	cout << "\nKMP for the rows of pattern\n";
	for (int i = 0; i < m_patSize; i++)
	{
		cout << m_kmpFArray[i] << ' ';
	}
	cout << '\n';
}
