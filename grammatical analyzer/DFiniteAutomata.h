#pragma once
#include "ParsingTable.h"
#include "State.h"
#include "NonTerminalSymbol.h"
#include "TerminalSymbol.h"

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
