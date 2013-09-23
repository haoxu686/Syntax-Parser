#include <algorithm>

#include "State.h"

State::State(int sizeNonTermSym)
{
	pvAcceptedSets = new vector<set<int> *>;
	pvCascadeSets = new vector<set<int> *>;
	set<int> * pSet;
	for (int i = 0; i < sizeNonTermSym; i++)
	{
		pSet = new set<int>;
		pvAcceptedSets->push_back(pSet);
		pSet = new set<int>;
		pvCascadeSets->push_back(pSet);
	}
	pvProjects = new vector<Project *>;
	pNextEdge = NULL;
}

State::~State(void)
{
	for (int i = 0; i < pvProjects->size(); i++)
	{
		delete pvProjects->at(i);
	}
	delete pvProjects;
	if (pNextEdge == NULL)
	{
		return;
	}
	else
	{
		delete pNextEdge;
	}
}

void State::addToAcceptedSet(int index, int value)
{
	pvAcceptedSets->at(index)->insert(value);
}

void State::addToCascadeSet(int index, int value)
{
	pvCascadeSets->at(index)->insert(value);
}

void State::addToAcceptedSet(int index, set<int>::iterator first, set<int>::iterator last)
{
	pvAcceptedSets->at(index)->insert(first, last);
}

set<int> * State::getAcceptedSetAt(int index)
{
	return pvAcceptedSets->at(index);
}

set<int> * State::getCascadeSetsAt(int index)
{
	return pvCascadeSets->at(index);
}

void State::addProject(Project * projInstance)
{
	pvProjects->push_back(projInstance);
}

void State::setNextEdge(Edge * edgeInstance)
{
	pNextEdge = edgeInstance;
}

void State::setIndex(int index)
{
	this->index = index;
}

bool State::equals(State * pState)
{
	if (pState->getProjectCount() != pvProjects->size())
	{
		return false;
	}
	for (int i = 0; i < pvProjects->size(); i++)
	{
		if (!pvProjects->at(i)->equals(pState->getProject(i)))
		{
			return false;
		}
	}
	return true;
}
void State::commit()
{
	sort(pvProjects->begin(), pvProjects->end(), State::sortMethod);
	Project * pProject;
	set<int> * pSet;
	set<int>::iterator it;
	for (int i = 0; i < pvProjects->size(); i++)
	{
		pProject = pvProjects->at(i);
		if (pProject->getLocationOfDot() != 0)
		{
			continue;
		}
		pSet = pvAcceptedSets->at(pProject->getProduction()->getNonTerminalSymbolOnLeft()->getIndexOfSymbol());
		pProject->addAcceptedSymbol(pSet->begin(), pSet->end());
	}
	for (int i = 0; i < pvAcceptedSets->size(); i++)
	{
		delete pvAcceptedSets->at(i);
		delete pvCascadeSets->at(i);
	}
	delete pvAcceptedSets;
	delete pvCascadeSets;
}

bool State::sortMethod(Project * p1, Project * p2)
{
	bool finish1 = p1->getProduction()->getSymbolOnRightCount() == p1->getLocationOfDot();
	bool finish2 = p2->getProduction()->getSymbolOnRightCount() == p2->getLocationOfDot();
	if (finish1 && !finish2)
	{
		return true;
	}
	else if (finish1 && finish2)
	{
		return false;
	}
	else if (!finish1 && finish2)
	{
		return false;
	}
	else
	{
		Symbol * p1Sym = p1->getProduction()->getSymbolOnRight(p1->getLocationOfDot());
		Symbol * p2Sym = p2->getProduction()->getSymbolOnRight(p2->getLocationOfDot());
		bool termp1 = p1Sym->isTerminalSymbol();
		bool termp2 = p2Sym->isTerminalSymbol();
		if (termp1 && !termp2)
		{
			return true;
		}
		else if (!termp1 && termp2)
		{
			return false;
		}
		else
		{
			return p1Sym->getIndexOfSymbol() < p2Sym->getIndexOfSymbol();
		}
	}
}

Edge * State::nextEdge()
{
	return pNextEdge;
}

int State::getProjectCount()
{
	return pvProjects->size();
}

Project * State::getProject(int index)
{
	return pvProjects->at(index);
}

int State::getIndex()
{
	return index;
}
