#include "Project.h"

Project::Project(int productionIndex, int dotLocation, Production * pProduction)
{
	this->productionIndex = productionIndex;
	this->dotLocation = dotLocation;
	this->pProduction = pProduction;
	psAcceptedSymbols = new set<int>;
}

Project::~Project(void)
{
	delete psAcceptedSymbols;
}

void Project::addAcceptedSymbol(int index)
{
	psAcceptedSymbols->insert(index);
}

void Project::addAcceptedSymbol(set<int>::iterator first, set<int>::iterator last)
{
	psAcceptedSymbols->insert(first, last);
}

int Project::getIndexOfProduction()
{
	return productionIndex;
}

Production * Project::getProduction()
{
	return pProduction;
}

int Project::getLocationOfDot()
{
	return dotLocation;
}

set<int> * Project::getAcceptedSymbols()
{
	return psAcceptedSymbols;
}

bool Project::equals(Project * pProject)
{
	if (pProject->getIndexOfProduction() != this->productionIndex)
	{
		return false;
	}
	if (pProject->getLocationOfDot() != this->dotLocation)
	{
		return false;
	}
	if (pProject->getAcceptedSymbols()->size() != this->psAcceptedSymbols->size())
	{
		return false;
	}
	set<int>::iterator it1;
	set<int>::iterator it2;
	for (it1 = pProject->getAcceptedSymbols()->begin(), it2 = psAcceptedSymbols->begin(); it2 != psAcceptedSymbols->end(); it1++, it2++)
	{
		if (*it1 != *it2)
		{
			return false;
		}
	}
	return true;
}
