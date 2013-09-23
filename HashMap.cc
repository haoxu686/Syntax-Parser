#include <cstdlib>

#include "HashMap.h"

HashMap::HashMap(void)
{
	pvHashMap = new vector<HashMapNode *>;
	HashMapNode * pNode;
	for (int i = 0; i < 1000; i++)
	{
		pNode = new HashMapNode();
		pNode->setSymbolId(-1);
		pNode->setSymbol(NULL);
		pNode->setNext(NULL);
		pvHashMap->push_back(pNode);
	}
}

HashMap::~HashMap(void)
{
	for (int i = 0; i < pvHashMap->size(); i++)
	{
		delete pvHashMap->at(i);
	}
	delete pvHashMap;
}

void HashMap::put(Symbol * key, int value)
{
	int hash = key->hashCode();
	hash = hash%pvHashMap->size();
	HashMapNode * pNode = pvHashMap->at(hash);
	HashMapNode * pNodePre = pNode;
	pNode = pNode->next();
	while (pNode != NULL)
	{
		if (pNode->getSymbol()->equals(key))
		{
			break;
		}
		pNodePre = pNode;
		pNode = pNode->next();
	}
	if (pNode == NULL)
	{
		pNode = new HashMapNode();
		pNode->setSymbolId(value);
		pNode->setSymbol(key);
		pNode->setNext(NULL);
		pNodePre->setNext(pNode);
	}
	else
	{
		pNode->setSymbolId(value);
		pNode->setSymbol(key);
	}
}

int HashMap::get(Symbol * key)
{
	int hash = key->hashCode();
	hash = hash%pvHashMap->size();
	HashMapNode * pNode = pvHashMap->at(hash);
	pNode = pNode->next();
	while (pNode != NULL)
	{
		if (pNode->getSymbol()->equals(key))
		{
			break;
		}
		pNode = pNode->next();
	}
	if (pNode == NULL)
	{
		return -1;
	}
	else
	{
		return pNode->getSymbolId();
	}
}

void HashMap::clear()
{
	HashMapNode * pNode;
	for (int i = 0; i < pvHashMap->size(); i++)
	{
		pNode = pvHashMap->at(i)->next();
		if (pNode == NULL)
		{
			continue;
		}
		else
		{
			delete pNode;
		}
	}
}
