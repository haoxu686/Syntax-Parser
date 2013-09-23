#pragma once
#include "Symbol.h"

class TerminalSymbol :
	public Symbol
{
private:
	int hash;
	char cTermChar;
	int index;
public:
	TerminalSymbol(char);
	~TerminalSymbol(void);
	int hashCode();
	bool isTerminalSymbol();
	bool equals(Symbol *);
	void setIndex(int);
	char getValue();
	int getIndexOfSymbol();
};
