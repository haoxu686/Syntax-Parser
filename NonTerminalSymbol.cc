#include <math.h>
#include <cstring>

#include "NonTerminalSymbol.h"

NonTerminalSymbol::NonTerminalSymbol(string * strValue)
{
	psValue = strValue;
	hash = 0;
	const char * p = strValue->data();
	int length = strlen(p);
	for (int i = 0; i < length; i++)
	{
		hash += (int)p[i]*pow(31.0, length-i-1);
	}
	hash = hash&0x7FFFFFFF;
	index = -1;
}

NonTerminalSymbol::~NonTerminalSymbol(void)
{
	delete psValue;
}

int NonTerminalSymbol::hashCode()
{
	return hash;
}

bool NonTerminalSymbol::isTerminalSymbol()
{
	return false;
}

bool NonTerminalSymbol::equals(Symbol * pSymbol)
{
	if (pSymbol->isTerminalSymbol())
	{
		return false;
	}
	else
	{
		NonTerminalSymbol * pNonTermSym = (NonTerminalSymbol *) pSymbol;
		if (psValue->compare(*pNonTermSym->getValue()) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void NonTerminalSymbol::setIndex(int index)
{
	this->index = index;
}

string * NonTerminalSymbol::getValue()
{
	return psValue;
}

int NonTerminalSymbol::getIndexOfSymbol()
{
	return index;
}
