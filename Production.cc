#include "Production.h"

Production::Production(void)
{
	pvSymRight = new vector<Symbol *>;
}

Production::~Production(void)
{
	delete pNonTermSymLeft;
	for (int i = 0; i < pvSymRight->size(); i++)
	{
		delete pvSymRight->at(i);
	}
	delete pvSymRight;
}

void Production::setNonTerminalSymbolOnLeft(NonTerminalSymbol * pNonTermLeft)
{
	pNonTermSymLeft = pNonTermLeft;
}

void Production::addSymbolOnRight(Symbol * pSym)
{
	pvSymRight->push_back(pSym);
}

NonTerminalSymbol * Production::getNonTerminalSymbolOnLeft()
{
	return pNonTermSymLeft;
}

int Production::getSymbolOnRightCount()
{
	return pvSymRight->size();
}

Symbol * Production::getSymbolOnRight(int index)
{
	return pvSymRight->at(index);
}
