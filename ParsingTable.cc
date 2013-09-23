#include "ParsingTable.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <stack>

ParsingTable::ParsingTable(int sizeState, vector<Production *> * pvProductions, vector<TerminalSymbol *> * pvTermSym, vector<NonTerminalSymbol *> * pvNonTermSym)
{
	this->pvProductions = pvProductions;
	this->pvTermSym = pvTermSym;
	this->pvNonTermSym = pvNonTermSym;
	vector<int> * pvTmp;
	pvAction = new vector<vector<int> *>;
	pvGoto = new vector<vector<int> *>;
	for (int i = 0; i < sizeState; i++)
	{
		pvTmp = new vector<int>;
		for (int j = 0; j < pvTermSym->size(); j++)
		{
			pvTmp->push_back(0);
		}
		pvAction->push_back(pvTmp);

		pvTmp = new vector<int>;
		for (int j = 0; j < pvNonTermSym->size(); j++)
		{
			pvTmp->push_back(0);
		}
		pvGoto->push_back(pvTmp);
	}
}

ParsingTable::~ParsingTable(void)
{
	for (int i = 0; i < pvAction->size(); i++)
	{
		delete pvAction->at(i);
	}
	for (int i = 0; i < pvGoto->size(); i++)
	{
		delete pvGoto->at(i);
	}
	delete pvAction;
	delete pvGoto;
}

void ParsingTable::setAction(int stateId, Symbol * key, int dstStateId)
{
	vector<int>::iterator it;
	if (key->isTerminalSymbol())
	{
		it = pvAction->at(stateId)->begin()+key->getIndexOfSymbol();
		*it = dstStateId;
	}
	else
	{
		it = pvGoto->at(stateId)->begin()+key->getIndexOfSymbol();
		*it = dstStateId;
	}
}

bool ParsingTable::analyse(string * expression)
{
	const char * sentence = expression->data();
	int length = strlen(sentence);
	int count;
	int operation;
	int curState;
	int index;
	Symbol * pSymbol;
	stack<Symbol *> * psSymbol = new stack<Symbol *>;
	stack<int> * psState = new stack<int>;
	psSymbol->push(pvTermSym->at(0));
	psState->push(0);
	curState = 0;
	for (int i = 0; i < length; i++)
	{
		index = -1;
		for(int j = 0; j < pvTermSym->size(); j++)
		{
			if (pvTermSym->at(j)->getValue() == sentence[i])
			{
				index = j;
			}
		}
		if (index == -1)
		{
			return false;
		}
		operation = pvAction->at(curState)->at(index);
		if (operation == 0)
		{
			return false;
		}
		else if (operation > 0)
		{
			curState = operation;
			psSymbol->push(pvTermSym->at(index));
			psState->push(curState);
			continue;
		}
		else
		{
			if (operation == -pvProductions->size())
			{
				return true;
			}
			else
			{
				operation = -operation;
				count = pvProductions->at(operation)->getSymbolOnRightCount();
				for (int j = 0; j < count; j++)
				{
					psState->pop();
					psSymbol->pop();
				}
				pSymbol = pvProductions->at(operation)->getNonTerminalSymbolOnLeft();
				psSymbol->push(pSymbol);
				curState = psState->top();
				operation = pvGoto->at(curState)->at(pSymbol->getIndexOfSymbol());
				curState = operation;
				psState->push(curState);
				i--;
				continue;
			}
		}
	}
		
	delete psState;
	delete psSymbol;
	return false;
}

void ParsingTable::showParsingTable()
{
	cout << endl;
	cout << "Parsing Table : " << endl;
	cout << setw(10) << ' ';
	for (int i = 0; i < pvTermSym->size(); i++)
	{
		cout << setw(10) << setiosflags(ios::left) << pvTermSym->at(i)->getValue();
	}
	for (int i = 0; i < pvNonTermSym->size(); i++)
	{
		cout << setw(10) << setiosflags(ios::left) << *pvNonTermSym->at(i)->getValue();
	}
	cout << endl;
	for (int i = 0; i < pvAction->size(); i++)
	{
		cout << setw(10) << setiosflags(ios::left) << i;
		for (int j = 0; j < pvTermSym->size(); j++)
		{
			cout << setw(10) << setiosflags(ios::left) << pvAction->at(i)->at(j);
		}
		for (int j = 0; j < pvNonTermSym->size(); j++)
		{
			cout << setw(10) << setiosflags(ios::left) << pvGoto->at(i)->at(j);
		}
		cout << endl;
	}
}
