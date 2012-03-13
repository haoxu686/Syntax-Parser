#include "StdAfx.h"
#include "DFiniteAutomata.h"
#include "Edge.h"

DFiniteAutomata::DFiniteAutomata(vector<Production *> * pvProductions, vector<NonTerminalSymbol *> * pvNonTermSym, vector<TerminalSymbol *> * pvTermSym)
{
	pvStates = new vector<State *>;
	this->pvProductions = pvProductions;
	this->pvNonTermSym = pvNonTermSym;
	this->pvTermSym = pvTermSym;
}

DFiniteAutomata::~DFiniteAutomata(void)
{
	for (int i = 0; i < pvStates->size(); i++)
	{
		delete pvStates->at(i);
	}
	delete pvStates;
}

void DFiniteAutomata::addState(State * stateInstance)
{
	stateInstance->setIndex(pvStates->size());
	pvStates->push_back(stateInstance);
}

void DFiniteAutomata::addEdge(int index, Edge * edgeInstance)
{
	State * pState = pvStates->at(index);
	Edge * pEdge;
	if (pState->nextEdge() == NULL)
	{
		pState->setNextEdge(edgeInstance);
	}
	else
	{
		pEdge = pState->nextEdge();
		while (pEdge->next() != NULL)
		{
			pEdge = pEdge->next();
		}
		pEdge->setNext(edgeInstance);
	}
}

int DFiniteAutomata::getStateCount()
{
	return pvStates->size();
}

State * DFiniteAutomata::getState(int index)
{
	return pvStates->at(index);
}

ParsingTable * DFiniteAutomata::toParsingTable()
{
	ParsingTable * pParsingTable = new ParsingTable(pvStates->size(), pvProductions, pvTermSym, pvNonTermSym);
	State * pState;
	Project * pProject;
	Edge * pEdge;
	Symbol * pSymbol;
	set<int>::iterator it;
	for (int i = 0; i < pvStates->size(); i++)
	{
		pState = pvStates->at(i);
		pEdge = pState->nextEdge();
		while (pEdge != NULL)
		{
			pParsingTable->setAction(pState->getIndex(), pEdge->getIdentifiedSymbol(), pEdge->getDstStateId());
			pEdge = pEdge->next();
		}
		for (int j = 0; j < pState->getProjectCount(); j++)
		{
			pProject = pState->getProject(j);
			if (pProject->getLocationOfDot() != pProject->getProduction()->getSymbolOnRightCount())
			{
				continue;
			}
			for (it = pProject->getAcceptedSymbols()->begin(); it != pProject->getAcceptedSymbols()->end(); it++)
			{
				pSymbol = pvTermSym->at(*it);
				if (pProject->getIndexOfProduction() == 0)
				{
					pParsingTable->setAction(pState->getIndex(), pSymbol, -pvProductions->size());
				}
				else
				{
					pParsingTable->setAction(pState->getIndex(), pSymbol, -(pProject->getIndexOfProduction()));
				}
			}
		}
	}
	return pParsingTable;
}

void DFiniteAutomata::showDFA()
{
	set<int> * pSet;
	set<int>::iterator it;
	Symbol * pSymbol;
	NonTerminalSymbol * pNonTermSym;
	TerminalSymbol * pTermSym;
	State * pState;
	Edge * pEdge;
	Project * pProject;
	Production * pProduction;
	cout << endl;
	cout << "DFA States : " << endl;
	for (int i = 0; i < pvStates->size(); i++)
	{
		pState = pvStates->at(i);
		cout << endl;
		cout << "I" << i << ": ";
		cout << "   ";
		pEdge = pState->nextEdge();
		while (pEdge != NULL)
		{
			pSymbol = pEdge->getIdentifiedSymbol();
			if (pSymbol->isTerminalSymbol())
			{
				pTermSym = (TerminalSymbol *) pSymbol;
				cout << pTermSym->getValue();
			}
			else
			{
				pNonTermSym = (NonTerminalSymbol *) pSymbol;
				cout << *pNonTermSym->getValue();
			}
			cout << ' ';
			cout << pEdge->getDstStateId();
			cout << "   ";
			pEdge = pEdge->next();
		}
		cout << endl;
		for (int j = 0; j < pState->getProjectCount(); j++)
		{
			pProject = pState->getProject(j);
			pProduction = pProject->getProduction();
			pNonTermSym = pProduction->getNonTerminalSymbolOnLeft();
			cout << *pNonTermSym->getValue() << " -> ";
			for (int k = 0; k < pProduction->getSymbolOnRightCount(); k++)
			{
				if (k == pProject->getLocationOfDot())
				{
					cout << '.';
				}
				pSymbol = pProduction->getSymbolOnRight(k);
				if (pSymbol->isTerminalSymbol())
				{
					pTermSym = (TerminalSymbol *) pSymbol;
					cout << pTermSym->getValue();
				}
				else
				{
					pNonTermSym = (NonTerminalSymbol *) pSymbol;
					cout << *pNonTermSym->getValue();
				}
			}
			if (pProject->getLocationOfDot() == pProduction->getSymbolOnRightCount())
			{
				cout << '.';
			}
			cout << " , ";
			pSet = pProject->getAcceptedSymbols();
			for (it = pSet->begin(); it != pSet->end(); it++)
			{
				cout << *it << "/";
			}
			cout << endl;
		}
	}
}