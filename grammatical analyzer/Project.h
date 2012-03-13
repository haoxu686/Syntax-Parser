#pragma once
#include "TerminalSymbol.h"
#include "Production.h"

class Project
{
private:
	int productionIndex;
	int dotLocation;
	Production * pProduction;
	set<int> * psAcceptedSymbols;
public:
	Project(int, int, Production *);
	~Project(void);
	void addAcceptedSymbol(int);
	void addAcceptedSymbol(set<int>::iterator first, set<int>::iterator last);
	int getIndexOfProduction();
	Production * getProduction();
	int getLocationOfDot();
	set<int> * getAcceptedSymbols();
	bool equals(Project *);
};
