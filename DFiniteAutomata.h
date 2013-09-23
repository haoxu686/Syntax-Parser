#pragma once

#include <vector>

#include "ParsingTable.h"
#include "State.h"
#include "NonTerminalSymbol.h"
#include "TerminalSymbol.h"

using namespace std;

class DFiniteAutomata
{
private:
	vector<State *> * pvStates;
	vector<Production *> * pvProductions;
	vector<NonTerminalSymbol *> * pvNonTermSym;
	vector<TerminalSymbol *> * pvTermSym;
public:
	DFiniteAutomata(vector<Production *> *, vector<NonTerminalSymbol *> *, vector<TerminalSymbol *> *);
	~DFiniteAutomata(void);
	void addState(State *);
	void addEdge(int, Edge *);
	int getStateCount();
	State * getState(int);
	ParsingTable * toParsingTable();
	void showDFA();
};
