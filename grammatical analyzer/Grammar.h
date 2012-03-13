#pragma once
#include "Production.h"
#include "TerminalSymbol.h"
#include "NonTerminalSymbol.h"
#include "DFiniteAutomata.h"
#include "Project.h"
#include "State.h"

class Grammar
{
private:
	vector<Production *> * pvProductions;
	vector<TerminalSymbol *> * pvTermSym;
	vector<NonTerminalSymbol *> * pvNonTermSym;
	vector<int> * pvNonTermSymLoc;
	vector<set<int> *> * pvFirstSets;
public:
	Grammar(void);
	~Grammar(void);
	void addProduction(Production *);
	void setTerminalSymbolSet(vector<TerminalSymbol *> *);
	void setNonTerminalSymbolSet(vector<NonTerminalSymbol *> *);
	set<int> * firstSetOf(int, vector<bool> *);
	void commit();
	void cascade(State *, Project *);
	void fullFillState(State *);
	void caclulateClosure(State *);
	DFiniteAutomata * toDFA();
	void showProductions();
	static bool sortMethod(Production *, Production *);
};
