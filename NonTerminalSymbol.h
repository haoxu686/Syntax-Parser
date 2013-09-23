#pragma once

#include <string>

#include "Symbol.h"

using namespace std;

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
