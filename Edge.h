#pragma once
#include "Symbol.h"

using namespace std;

class Edge
{
private:
	int dstStateId;
	Symbol * psIdentifiedSymbol;
	Edge * pNextEdge;
public:
	Edge(void);
	~Edge(void);
	int getDstStateId();
	Symbol * getIdentifiedSymbol();
	Edge * next();
	void setDstStateId(int);
	void setIdentifiedSymbol(Symbol *);
	void setNext(Edge *);
};
