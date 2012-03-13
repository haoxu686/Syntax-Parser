#pragma once
#include "TerminalSymbol.h"
#include "NonTerminalSymbol.h"
#include "Production.h"

class ParsingTable
{
private:
	vector<Production *> * pvProductions;
	vector<TerminalSymbol *> * pvTermSym;
	vector<NonTerminalSymbol *> * pvNonTermSym;
	vector<vector<int> *> * pvAction;
	vector<vector<int> *> * pvGoto;
public:
	ParsingTable(int, vector<Production *> *, vector<TerminalSymbol *> *, vector<NonTerminalSymbol *> *);
	~ParsingTable(void);
	void setAction(int, Symbol *, int);
	bool analyse(string *);
	void showParsingTable();
};
