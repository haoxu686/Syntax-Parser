#include "StdAfx.h"
#include "Grammar.h"
#include "HashMap.h"
#include "Edge.h"

Grammar::Grammar(void)
{
	pvProductions = new vector<Production *>;
	pvNonTermSymLoc = new vector<int>;
	pvFirstSets = new vector<set<int> *>;
}

Grammar::~Grammar(void)
{
	for (int i = 0; i < pvProductions->size(); i++)
	{
		delete pvProductions->at(i);
	}
	delete pvProductions;
	delete pvTermSym->at(0);
	delete pvNonTermSymLoc;
	for (int i = 0; i < pvFirstSets->size(); i++)
	{
		delete pvFirstSets->at(i);
	}
	delete pvFirstSets;
	delete pvTermSym;
	delete pvNonTermSym;
}

bool Grammar::sortMethod(Production * p1, Production * p2)
{
	int indexOfP1 = p1->getNonTerminalSymbolOnLeft()->getIndexOfSymbol();
	int indexOfP2 = p2->getNonTerminalSymbolOnLeft()->getIndexOfSymbol();
	if (indexOfP1 < indexOfP2)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Grammar::addProduction(Production * productionInstance)
{
	pvProductions->push_back(productionInstance);
}

void Grammar::setTerminalSymbolSet(vector<TerminalSymbol*> * pvTermSym)
{
	this->pvTermSym = pvTermSym;
}

void Grammar::setNonTerminalSymbolSet(vector<NonTerminalSymbol*> * pvNonTermSym)
{
	this->pvNonTermSym = pvNonTermSym;
}

set<int> * Grammar::firstSetOf(int indexNonTermSym, vector<bool> * pvMarks)
{
	set<int> * pResSet = new set<int>;
	set<int> * pSet;
	set<int>::iterator sIt;
	Symbol * pSymbol;
	vector<bool>::iterator vIt;
	for (int i = pvNonTermSymLoc->at(indexNonTermSym); i < pvNonTermSymLoc->at(indexNonTermSym+1); i++)
	{
		pResSet->insert(-2);
		for (int j = 0; j < pvProductions->at(i)->getSymbolOnRightCount(); j++)
		{
			sIt = pResSet->find(-2);
			if (sIt != pResSet->end())
			{
				pResSet->erase(sIt);
			}

			pSymbol = pvProductions->at(i)->getSymbolOnRight(j);
			if (pSymbol->isTerminalSymbol())
			{
				pResSet->insert(pSymbol->getIndexOfSymbol());
				pvFirstSets->at(indexNonTermSym)->insert(pSymbol->getIndexOfSymbol());
				break;
			}
			vIt = pvMarks->begin()+pSymbol->getIndexOfSymbol();
			if (*vIt)
			{
				sIt = pvFirstSets->at(pSymbol->getIndexOfSymbol())->find(-1);
				if (sIt != pvFirstSets->at(pSymbol->getIndexOfSymbol())->end())
				{
					continue;
				}
				else
				{
					break;
				}
			}
			*vIt = true;
			if (pvFirstSets->at(pSymbol->getIndexOfSymbol())->size() != 0)
			{
				pSet = pvFirstSets->at(pSymbol->getIndexOfSymbol());
				pResSet->insert(pSet->begin(), pSet->end());
				sIt = pResSet->find(-1);
				if (sIt != pResSet->end())
				{
					pResSet->erase(sIt);
					pResSet->insert(-2);
					*vIt = false;
				}
				else
				{
					break;
				}
			}
			else
			{
				pSet = this->firstSetOf(pSymbol->getIndexOfSymbol(), pvMarks);
				pResSet->insert(pSet->begin(), pSet->end());
				delete pSet;
				sIt = pResSet->find(-1);
				if (sIt != pResSet->end())
				{
					pResSet->erase(sIt);
					pResSet->insert(-2);
					*vIt = false;
				}
				else
				{
					break;
				}
			}
		}
		sIt = pResSet->find(-2);
		if (sIt != pResSet->end())
		{
			pResSet->erase(sIt);
			pResSet->insert(-1);
			pvFirstSets->at(indexNonTermSym)->insert(-1);
		}
	}
	return pResSet;
}

void Grammar::commit()
{
	Production * pProduction = new Production();
	pProduction->setNonTerminalSymbolOnLeft(pvNonTermSym->at(0));
	string * psStart = new string(*pvNonTermSym->at(1)->getValue());
	NonTerminalSymbol * pNonTermSym = new NonTerminalSymbol(psStart);
	pNonTermSym->setIndex(pvNonTermSym->at(1)->getIndexOfSymbol());
	pProduction->addSymbolOnRight(pNonTermSym);
	pvProductions->insert(pvProductions->begin(), pProduction);

	sort(pvProductions->begin(), pvProductions->end(), Grammar::sortMethod);
	pvNonTermSymLoc->push_back(0);
	for (int i = 1; i < pvProductions->size(); i++)
	{
		if (pvProductions->at(i)->getNonTerminalSymbolOnLeft()->getIndexOfSymbol() != pvProductions->at(i-1)->getNonTerminalSymbolOnLeft()->getIndexOfSymbol())
		{
			pvNonTermSymLoc->push_back(i);
		}
	}
	pvNonTermSymLoc->push_back(pvProductions->size());

	for (int i = 0; i < pvNonTermSym->size(); i++)
	{
		pvFirstSets->push_back(new set<int>);
	}

	vector<bool> * pvMarks = new vector<bool>;
	vector<bool>::iterator vIt;
	set<int> * pSet;
	set<int>::iterator sIt;
	int sizePre;
	int sizeLater;
	bool flag = false;
	for (int i = 0; i < pvNonTermSym->size(); i++)
	{
		pvMarks->push_back(false);
	}
	do
	{
		flag = false;
		for (int i = 1; i < pvNonTermSym->size(); i++)
		{
			for (vIt = pvMarks->begin(); vIt != pvMarks->end(); vIt++)
			{
				*vIt = false;
			}
			vIt = pvMarks->begin()+i;
			*vIt = true;
			pSet = this->firstSetOf(i, pvMarks);
			sizePre = pvFirstSets->at(i)->size();
			pvFirstSets->at(i)->insert(pSet->begin(), pSet->end());
			sizeLater = pvFirstSets->at(i)->size();
			if (sizePre != sizeLater)
			{
				flag = true;
			}
			delete pSet;
		}
	}while(flag);
	delete pvMarks;
}

void Grammar::cascade(State * pState, Project * pProject)
{
	set<int> * pSet;
	set<int> * pCascadeSet;
	set<int> * psFirstSet;
	set<int>::iterator it;
	bool flag = false;
	Symbol * pSymbol;
	Production * pProduction = pProject->getProduction();
	int indexNonTerm = pProduction->getSymbolOnRight(pProject->getLocationOfDot())->getIndexOfSymbol();

	for (int i = pProject->getLocationOfDot()+1; i < pProduction->getSymbolOnRightCount(); i++)
	{
		pSymbol = pProduction->getSymbolOnRight(i);
		if (pSymbol->isTerminalSymbol())
		{
			pState->addToAcceptedSet(indexNonTerm, pSymbol->getIndexOfSymbol());
			flag = true;
			break;
		}
		else
		{
			psFirstSet = pvFirstSets->at(pSymbol->getIndexOfSymbol());
			pState->addToAcceptedSet(indexNonTerm, psFirstSet->begin(), psFirstSet->end());
			it = psFirstSet->find(-1);
			if (it == psFirstSet->end())
			{
				flag = true;
				break;
			}
			else
			{
				pSet = pState->getAcceptedSetAt(indexNonTerm);
				it = pSet->find(-1);
				pSet->erase(it);
			}
		}
	}

	if (!flag)
	{
		pSet = pProject->getAcceptedSymbols();
		if (pSet->size() == 0)
		{
			pSet = pState->getAcceptedSetAt(pProduction->getNonTerminalSymbolOnLeft()->getIndexOfSymbol());
		}
		pState->addToAcceptedSet(indexNonTerm, pSet->begin(), pSet->end());
		pState->addToCascadeSet(pProduction->getNonTerminalSymbolOnLeft()->getIndexOfSymbol(), indexNonTerm);
	}

	pCascadeSet = pState->getCascadeSetsAt(indexNonTerm);
	pSet = pState->getAcceptedSetAt(indexNonTerm);
	for (it = pCascadeSet->begin(); it != pCascadeSet->end(); it++)
	{
		pState->addToAcceptedSet(*it, pSet->begin(), pSet->end());
	}
}

void Grammar::fullFillState(State * pState)
{
	int curNonTermSym;
	Project * pProject;
	Symbol * pSymbol;
	set<int> * psUndoNonTermSym = new set<int>;
	set<int>::iterator it;
	queue<int> * pqNonTermSym = new queue<int>;
	for (int i = 0; i < pState->getProjectCount(); i++)
	{
		pProject = pState->getProject(i);
		if (pProject->getLocationOfDot() == pProject->getProduction()->getSymbolOnRightCount())
		{
			continue;
		}
		pSymbol = pProject->getProduction()->getSymbolOnRight(pProject->getLocationOfDot());
		if (pSymbol->isTerminalSymbol())
		{
			continue;
		}
		it = psUndoNonTermSym->find(pSymbol->getIndexOfSymbol());
		if (it == psUndoNonTermSym->end())
		{
			psUndoNonTermSym->insert(pSymbol->getIndexOfSymbol());
			pqNonTermSym->push(pSymbol->getIndexOfSymbol());
		}
	}
	while (!pqNonTermSym->empty())
	{
		curNonTermSym = pqNonTermSym->front();
		pqNonTermSym->pop();
		for (int i = pvNonTermSymLoc->at(curNonTermSym); i < pvNonTermSymLoc->at(curNonTermSym+1); i++)
		{
			pProject = new Project(i, 0, pvProductions->at(i));
			pState->addProject(pProject);
			if (pvProductions->at(i)->getSymbolOnRightCount() == 0)
			{
				continue;
			}
			pSymbol = pvProductions->at(i)->getSymbolOnRight(0);
			if (pSymbol->isTerminalSymbol())
			{
				continue;
			}
			it = psUndoNonTermSym->find(pSymbol->getIndexOfSymbol());
			if (it != psUndoNonTermSym->end())
			{
				continue;
			}
			psUndoNonTermSym->insert(pSymbol->getIndexOfSymbol());
			pqNonTermSym->push(pSymbol->getIndexOfSymbol());
		}
	}
	delete pqNonTermSym;
	delete psUndoNonTermSym;
}

void Grammar::caclulateClosure(State * pState)
{
	Project * pProject;
	Symbol * pSymbol;
	int sizePre;
	int sizeLater;
	bool flag;
	do
	{
		flag = false;
		for (int i = 0; i < pState->getProjectCount(); i++)
		{
			pProject = pState->getProject(i);
			if (pProject->getLocationOfDot() == pProject->getProduction()->getSymbolOnRightCount())
			{
				continue;
			}
			pSymbol = pProject->getProduction()->getSymbolOnRight(pProject->getLocationOfDot());
			if (pSymbol->isTerminalSymbol())
			{
				continue;
			}
			sizePre = pState->getAcceptedSetAt(pSymbol->getIndexOfSymbol())->size();
			this->cascade(pState, pProject);
			sizeLater = pState->getAcceptedSetAt(pSymbol->getIndexOfSymbol())->size();
			if (sizePre != sizeLater)
			{
				flag = true;
			}
		}
	}while(flag);
}

DFiniteAutomata * Grammar::toDFA()
{
	DFiniteAutomata * pDFiniteAutomata = new DFiniteAutomata(pvProductions,pvNonTermSym, pvTermSym);
	queue<State *> * pqUndoStates = new queue<State *>;
	int i = 0;
	int j = 0;
	Edge * pEdge;
	Symbol * pSymbol;
	State * pState;
	State * pCurState;
	Project * pProject;
	Project * pCurProject;
	pState = new State(pvNonTermSym->size());
	pProject = new Project(0, 0, pvProductions->at(0));
	pProject->addAcceptedSymbol(0);
	pState->addProject(pProject);
	this->fullFillState(pState);
	this->caclulateClosure(pState);
	pState->commit();
	pDFiniteAutomata->addState(pState);
	pqUndoStates->push(pState);
	while (!pqUndoStates->empty())
	{
		pCurState = pqUndoStates->front();
		pqUndoStates->pop();
		i = 0;
		pCurProject = pCurState->getProject(i);
		while (pCurProject->getLocationOfDot() == pCurProject->getProduction()->getSymbolOnRightCount())
		{
			i++;
			if (i == pCurState->getProjectCount())
			{
				break;
			}
			pCurProject = pCurState->getProject(i);
		}
		if (i == pCurState->getProjectCount())
		{
			continue;
		}
		pState = new State(pvNonTermSym->size());
		pProject = new Project(pCurProject->getIndexOfProduction(), pCurProject->getLocationOfDot()+1, pCurProject->getProduction());
		pProject->addAcceptedSymbol(pCurProject->getAcceptedSymbols()->begin(), pCurProject->getAcceptedSymbols()->end());
		pState->addProject(pProject);
		i++;
		while (i < pCurState->getProjectCount())
		{
			pSymbol = pCurProject->getProduction()->getSymbolOnRight(pCurProject->getLocationOfDot());
			pCurProject = pCurState->getProject(i);
			if (pCurProject->getProduction()->getSymbolOnRight(pCurProject->getLocationOfDot())->equals(pSymbol))
			{
				pProject = new Project(pCurProject->getIndexOfProduction(), pCurProject->getLocationOfDot()+1, pCurProject->getProduction());
				pProject->addAcceptedSymbol(pCurProject->getAcceptedSymbols()->begin(), pCurProject->getAcceptedSymbols()->end());
				pState->addProject(pProject);
				i++;
				continue;
			}
			else
			{
				this->fullFillState(pState);
				this->caclulateClosure(pState);
				pState->commit();
				for (j = 0; j < pDFiniteAutomata->getStateCount(); j++)
				{
					if (pDFiniteAutomata->getState(j)->equals(pState))
					{
						delete pState;
						pState = pDFiniteAutomata->getState(j);
						pEdge = new Edge();
						pEdge->setIdentifiedSymbol(pSymbol);
						pEdge->setDstStateId(pState->getIndex());
						pDFiniteAutomata->addEdge(pCurState->getIndex(), pEdge);
						break;
					}
				}
				if (j == pDFiniteAutomata->getStateCount())
				{
					pDFiniteAutomata->addState(pState);
					pEdge = new Edge();
					pEdge->setDstStateId(pState->getIndex());
					pEdge->setIdentifiedSymbol(pSymbol);
					pDFiniteAutomata->addEdge(pCurState->getIndex(), pEdge);
					pqUndoStates->push(pState);
				}
				pState = new State(pvNonTermSym->size());
				pProject = new Project(pCurProject->getIndexOfProduction(), pCurProject->getLocationOfDot()+1, pCurProject->getProduction());
				pProject->addAcceptedSymbol(pCurProject->getAcceptedSymbols()->begin(), pCurProject->getAcceptedSymbols()->end());
				pState->addProject(pProject);
				i++;
				continue;
			}
		}
		this->fullFillState(pState);
		this->caclulateClosure(pState);
		pState->commit();
		pSymbol = pCurProject->getProduction()->getSymbolOnRight(pCurProject->getLocationOfDot());
		for (j = 0; j < pDFiniteAutomata->getStateCount(); j++)
		{
			if (pDFiniteAutomata->getState(j)->equals(pState))
			{
				delete pState;
				pState = pDFiniteAutomata->getState(j);
				pEdge = new Edge();
				pEdge->setIdentifiedSymbol(pSymbol);
				pEdge->setDstStateId(pState->getIndex());
				pDFiniteAutomata->addEdge(pCurState->getIndex(), pEdge);
				break;
			}
		}
		if (j == pDFiniteAutomata->getStateCount())
		{
			pDFiniteAutomata->addState(pState);
			pEdge = new Edge();
			pEdge->setDstStateId(pState->getIndex());
			pEdge->setIdentifiedSymbol(pSymbol);
			pDFiniteAutomata->addEdge(pCurState->getIndex(), pEdge);
			pqUndoStates->push(pState);
		}
	}
	delete pqUndoStates;
	return pDFiniteAutomata;
}

void Grammar::showProductions()
{
	Production * pp;
	NonTerminalSymbol * pNonTerm;
	TerminalSymbol * pTerm;
	cout << "Productions : " << endl;
	for (int i = 0; i < pvProductions->size(); i++)
	{
		cout << i << ' ' << *pvProductions->at(i)->getNonTerminalSymbolOnLeft()->getValue() << " -> ";
		pp = pvProductions->at(i);
		for (int j = 0; j < pp->getSymbolOnRightCount(); j++)
		{
			if (pp->getSymbolOnRight(j)->isTerminalSymbol())
			{
				pTerm = (TerminalSymbol *) pp->getSymbolOnRight(j);
				cout << pTerm->getValue();
			}
			else
			{
				pNonTerm = (NonTerminalSymbol *) pp->getSymbolOnRight(j);
				cout << *pNonTerm->getValue();
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "TerminalSymbols : " << endl;
	cout << setw(15) << setiosflags(ios::left) << "Index";
	cout << "Value" << endl;
	for (int i = 0; i < pvTermSym->size(); i++)
	{
		cout << setw(15) << setiosflags(ios::left) << pvTermSym->at(i)->getIndexOfSymbol();
		cout << pvTermSym->at(i)->getValue();
		cout << endl;
	}
	cout << endl;

	cout << "NonTerminalSymbols : " << endl;
	cout << setw(15) << setiosflags(ios::left) << "Index";
	cout << "Value" << endl;
	for (int i = 0; i < pvNonTermSym->size(); i++)
	{
		cout << setw(15) << setiosflags(ios::left) << pvNonTermSym->at(i)->getIndexOfSymbol();
		cout << *pvNonTermSym->at(i)->getValue();
		cout << endl;
	}
	cout << endl;

	cout << "FirstSets : " << endl;
	cout << setw(25) << setiosflags(ios::left) << "NonTerminalSymbol";
	cout << "FirstSet" << endl;
	set<int>::iterator it;
	for (int i = 0; i < pvFirstSets->size(); i++)
	{
		cout << setw(25) << setiosflags(ios::left) << i;
		for (it = pvFirstSets->at(i)->begin(); it != pvFirstSets->at(i)->end(); it++)
		{
			cout << *it << ',';
		}
		cout << endl;
	}
}
