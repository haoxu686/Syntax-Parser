#include "StdAfx.h"
#include "HashMapNode.h"

HashMapNode::HashMapNode(void)
{
	pNodeNext = NULL;
}

HashMapNode::~HashMapNode(void)
{
	if (pNodeNext == NULL)
	{
		return;
	}
	else
	{
		delete pNodeNext;
	}
}

int HashMapNode::getSymbolId()
{
	return id;
}

Symbol * HashMapNode::getSymbol()
{
	return pSymbol;
}

HashMapNode * HashMapNode::next()
{
	return pNodeNext;
}

void HashMapNode::setSymbolId(int id)
{
	this->id = id;
}

void HashMapNode::setSymbol(Symbol * pSymbol)
{
	this->pSymbol = pSymbol;
}

void HashMapNode::setNext(HashMapNode * pNext)
{
	pNodeNext = pNext;
}
