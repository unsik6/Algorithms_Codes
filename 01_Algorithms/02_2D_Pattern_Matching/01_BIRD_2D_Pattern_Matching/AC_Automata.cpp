#include "AC_Automata.h"

int AC_Automata::gotoFunc(int _state, int _symbol)	// return value -2(error), -1(fail), else(state)
{
	if (_state >= m_automaton.size() || _state < 0)
	{
		cerr << "ERORR: Input state " << _state << "doesn't exist.\n";
		return -2;
	}

	for (list<edgePair*>::iterator iter = m_automaton[_state]->begin(); iter != m_automaton[_state]->end(); iter++)
	{
		if ((*iter)->symbol == _symbol)
		{
			return (*iter)->dstState;
		}
	}

	// state 0 exception
	if (_state == 0)
		return 0;

	// There is no state from given state by given symbol
	return -1;
}

void AC_Automata::construct(vector<string>* _patArr)
{
	m_patterns = new string[_patArr->size()];
	m_patternNum = _patArr->size();
	// construct Goto
	for (int i = 0; i < _patArr->size(); i++)
	{
		int curState = 0;
		m_patterns[i] = _patArr->at(i);
		for (int j = 0; j < _patArr->at(i).length(); j++)
		{
			int retGoto = gotoFunc(curState, _patArr->at(i)[j]);
			if (retGoto == -1 || retGoto == 0)
			{
				m_automaton.push_back(new list<edgePair*>);
				m_outputs.push_back(new vector<int>);

				int nextStat = (int)m_automaton.size() - 1;
				m_automaton[curState]->push_back(new edgePair{ _patArr->at(i)[j], nextStat });
				curState = nextStat;
			}
			else
			{
				curState = retGoto;
			}
		}

		m_outputs[curState]->push_back(i);
	}

	// consturct failure
	m_failure = new int[(int)m_automaton.size()]{ 0 };

	queue<int> fQue;
	for (list<edgePair*>::iterator iter = m_automaton[0]->begin(); iter != m_automaton[0]->end(); iter++)
	{
		fQue.push(((*iter)->dstState));
		m_failure[(*iter)->dstState] = 0;
	}

	while (!fQue.empty())
	{
		int rStat = fQue.front();
		fQue.pop();

		for (list<edgePair*>::iterator iter = m_automaton[rStat]->begin(); iter != m_automaton[rStat]->end(); iter++)
		{
			int sStat = (*iter)->dstState;
			int stat = m_failure[rStat];
			fQue.push(sStat);
			while (gotoFunc(stat, (*iter)->symbol) == -1)
				stat = m_failure[stat];

			m_failure[sStat] = gotoFunc(stat, (*iter)->symbol);

			for (int i = 0; i < m_outputs[m_failure[sStat]]->size(); i++)
			{
				m_outputs[sStat]->push_back((*m_outputs[m_failure[sStat]])[i]);
			}
		}
	}
}

void AC_Automata::patternMatching(string _txt)
{
	int curState = 0;
	vector<int>* patPos = new vector<int>[m_patternNum];
	for (int i = 0; i < _txt.length(); i++)
	{
		while (gotoFunc(curState, _txt[i]) == -1)
			curState = m_failure[curState];
		curState = gotoFunc(curState, _txt[i]);

		if (!m_outputs[curState]->empty())
		{
			for (int j = 0; j < m_outputs[curState]->size(); j++)
			{
				patPos[m_outputs[curState]->at(j)].push_back(i);
			}
		}
	}

	// print locations of each pattern
	cout << "Pattern Matching|n";
	for (int i = 0; i < m_patternNum; i++)
	{
		cout << m_patterns[i] << " | ";
		for (int j = 0; j < patPos[i].size(); j++)
		{
			cout << patPos[i][j] << ", ";
		}
		cout << endl;
	}
	delete[] patPos;
}

void AC_Automata::printForCheck()
{
	cout << "automaton\n" << "the number of state: " << m_automaton.size() << endl;
	for (int s = 0; s < m_automaton.size(); s++)
	{
		cout << s << " |  ";
		for (list<edgePair*>::iterator iter = m_automaton[s]->begin(); iter != m_automaton[s]->end(); iter++)
			cout << '(' << (*iter)->symbol << ", " << (*iter)->dstState << "), ";
		cout << endl;
	}

	cout << "\nfailure Func\n";
	for (int i = 0; i < m_automaton.size(); i++)
	{
		cout << '(' << i << ", " << m_failure[i] << "), ";
	}
	cout << endl;

	cout << "outputs\n";
	for (int s = 0; s < m_outputs.size(); s++)
	{
		cout << s << " |  ";
		for (int i = 0; i < m_outputs[s]->size(); i++)
		{
			cout << m_patterns[m_outputs[s]->at((size_t)i)] << ", ";
		}

		cout << endl;
	}
}