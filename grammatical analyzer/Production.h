#pragma once
#include "Symbol.h"
#include "NonTerminalSymbol.h"

class Production
{
private:
	NonTerminalSymbol * pNonTermSymLeft;
	vector<Symbol *> * pvSymRight;
public:
	Production(void);
	~Production(void);
	void setNonTerminalSymbolOnLeft(NonTerminalSymbol *);
	void addSymbolOnRight(Symbol *);
	NonTerminalSymbol * getNonTerminalSymbolOnLeft();
	int getSymbolOnRightCount();
	Symbol * getSymbolOnRight(int);
};
