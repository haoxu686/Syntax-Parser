// grammatical analyzer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include "Grammar.h"
#include "Production.h"
#include "NonTerminalSymbol.h"
#include "TerminalSymbol.h"
#include "HashMap.h"
#include "DFiniteAutomata.h"
#include "ParsingTable.h"

int main()
{
	fstream infile("1.txt", ios::in);
	if (!infile)
	{
		cout << "cannot open file 1.txt" << endl;
		return 1;
	}

	Grammar * pGrammar = new Grammar();
	Production * pProduction = NULL;
	NonTerminalSymbol * pNonTermSymLeft = NULL;
	NonTerminalSymbol * pNonTermSymRight = NULL;
	TerminalSymbol * pTermSym = NULL;
	HashMap * pHashMap = new HashMap();
	vector<TerminalSymbol *> * pvTermSym = new vector<TerminalSymbol *>;
	pTermSym = new TerminalSymbol('#');
	pTermSym->setIndex(0);
	pvTermSym->push_back(pTermSym);
	vector<NonTerminalSymbol *> * pvNonTermSym = new vector<NonTerminalSymbol *>;
	pNonTermSymLeft = new NonTerminalSymbol(new string(""));
	pNonTermSymLeft->setIndex(0);
	pvNonTermSym->push_back(pNonTermSymLeft);

	int startPoint;
	int leftEdge;
	int rightEdge;
	string * psProduction = new string();
	string * psNonTerm;
	int indexSeperator;
	int symbolId;
	char buffer[3000];
	while (infile.getline(buffer, 3000))
	{
		psProduction->assign(buffer);
		indexSeperator = psProduction->find("->");
		psNonTerm = new string();
		*psNonTerm = psProduction->substr(0, indexSeperator);
		pNonTermSymLeft = new NonTerminalSymbol(psNonTerm);
		symbolId = pHashMap->get(pNonTermSymLeft);
		if (symbolId < 0)
		{
			pNonTermSymLeft->setIndex(pvNonTermSym->size());
			pHashMap->put(pNonTermSymLeft, pvNonTermSym->size());
			pvNonTermSym->push_back(pNonTermSymLeft);
		}
		else
		{
			pNonTermSymLeft->setIndex(symbolId);
		}
		pProduction = new Production();
		pProduction->setNonTerminalSymbolOnLeft(pNonTermSymLeft);
		indexSeperator += 2;

		startPoint = indexSeperator;
		leftEdge = -1;
		rightEdge = -1;
		for (int i = indexSeperator; i < psProduction->size(); i++)
		{
			if (psProduction->at(i) != '<' && psProduction->at(i) != '>')
			{
				continue;
			}
			else if (psProduction->at(i) == '<')
			{
				leftEdge = i;
				continue;
			}
			else if (psProduction->at(i) == '>')
			{
				if (leftEdge < 0)
				{
					continue;
				}
				else
				{
					rightEdge = i+1;
					for (int j = startPoint; j < leftEdge; j++)
					{
						pTermSym = new TerminalSymbol(psProduction->at(j));
						symbolId = pHashMap->get(pTermSym);
						if (symbolId < 0)
						{
							pTermSym->setIndex(pvTermSym->size());
							pHashMap->put(pTermSym, pvTermSym->size());
							pvTermSym->push_back(pTermSym);
						}
						else
						{
							pTermSym->setIndex(symbolId);
						}
						pProduction->addSymbolOnRight(pTermSym);
					}
					psNonTerm = new string();
					*psNonTerm = psProduction->substr(leftEdge, rightEdge-leftEdge);
					pNonTermSymRight = new NonTerminalSymbol(psNonTerm);
					symbolId = pHashMap->get(pNonTermSymRight);
					if (symbolId < 0)
					{
						pNonTermSymRight->setIndex(pvNonTermSym->size());
						pHashMap->put(pNonTermSymRight, pvNonTermSym->size());
						pvNonTermSym->push_back(pNonTermSymRight);
					}
					else
					{
						pNonTermSymRight->setIndex(symbolId);
					}
					pProduction->addSymbolOnRight(pNonTermSymRight);
					startPoint = i+1;
					leftEdge = -1;
				}
			}
		}
		for (int i = startPoint; i < psProduction->size(); i++)
		{
			pTermSym = new TerminalSymbol(psProduction->at(i));
			symbolId = pHashMap->get(pTermSym);
			if (symbolId < 0)
			{
				pTermSym->setIndex(pvTermSym->size());
				pHashMap->put(pTermSym, pvTermSym->size());
				pvTermSym->push_back(pTermSym);
			}
			else
			{
				pTermSym->setIndex(symbolId);
			}
			pProduction->addSymbolOnRight(pTermSym);
		}
		pGrammar->addProduction(pProduction);
	}
	pGrammar->setTerminalSymbolSet(pvTermSym);
	pGrammar->setNonTerminalSymbolSet(pvNonTermSym);
	pGrammar->commit();
	pGrammar->showProductions();
	DFiniteAutomata * pDFiniteAutomata = pGrammar->toDFA();
	pDFiniteAutomata->showDFA();
	ParsingTable * pParsingTable = pDFiniteAutomata->toParsingTable();
	pParsingTable->showParsingTable();
	string * sentence = new string();
	bool result;
	cin >> *sentence;
	while (sentence->compare("exit") != 0)
	{
		result = pParsingTable->analyse(sentence);
		if (result)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
		cin >> *sentence;
	}

	delete sentence;
	delete pHashMap;
	delete psProduction;
	delete pDFiniteAutomata;
	delete pGrammar;
	return 0;
}

