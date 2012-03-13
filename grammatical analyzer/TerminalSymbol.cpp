#include "StdAfx.h"
#include "TerminalSymbol.h"

TerminalSymbol::TerminalSymbol(char termChar)
{
	cTermChar = termChar;
	hash = (int)cTermChar;
	index = -1;
}

TerminalSymbol::~TerminalSymbol(void)
{
}

int TerminalSymbol::hashCode()
{
	return hash;
}

bool TerminalSymbol::isTerminalSymbol()
{
	return true;
}

bool TerminalSymbol::equals(Symbol * pSymbol)
{
	if (!pSymbol->isTerminalSymbol())
	{
		return false;
	}
	else
	{
		TerminalSymbol * pTermSym = (TerminalSymbol *) pSymbol;
		if (cTermChar == pTermSym->getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void TerminalSymbol::setIndex(int index)
{
	this->index = index;
}

char TerminalSymbol::getValue()
{
	return cTermChar;
}

int TerminalSymbol::getIndexOfSymbol()
{
	return index;
}