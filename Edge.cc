#include <cstdlib>

#include "Edge.h"

Edge::Edge(void)
{
	pNextEdge = NULL;
}

Edge::~Edge(void)
{
	if (pNextEdge == NULL)
	{
		return;
	}
	else
	{
		delete pNextEdge;
	}
}

int Edge::getDstStateId()
{
	return dstStateId;
}

Symbol * Edge::getIdentifiedSymbol()
{
	return psIdentifiedSymbol;
}

Edge * Edge::next()
{
	return pNextEdge;
}

void Edge::setDstStateId(int id)
{
	dstStateId = id;
}

void Edge::setIdentifiedSymbol(Symbol * psSymbol)
{
	psIdentifiedSymbol = psSymbol;
}

void Edge::setNext(Edge * next)
{
	pNextEdge = next;
}
