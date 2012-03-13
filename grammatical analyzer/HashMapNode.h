#pragma once
#include "Symbol.h"

class HashMapNode
{
private:
	int id;
	Symbol * pSymbol;
	HashMapNode * pNodeNext;
public:
	HashMapNode(void);
	~HashMapNode(void);
	int getSymbolId();
	Symbol * getSymbol();
	HashMapNode * next();
	void setSymbolId(int);
	void setSymbol(Symbol *);
	void setNext(HashMapNode *);
};
