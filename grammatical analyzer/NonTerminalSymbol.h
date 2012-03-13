#pragma once
#include "symbol.h"

class NonTerminalSymbol :
	public Symbol
{
private:
	string * psValue;
	int index;
	int hash;
public:
	NonTerminalSymbol(string *);
	~NonTerminalSymbol(void);
	int hashCode();
	bool isTerminalSymbol();
	bool equals(Symbol *);
	void setIndex(int);
	string * getValue();
	int getIndexOfSymbol();
};
