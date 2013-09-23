#pragma once
#include <vector>

#include "HashMapNode.h"

using namespace std;

class HashMap
{
private:
	vector<HashMapNode *> * pvHashMap;
public:
	HashMap(void);
	~HashMap(void);
	void put(Symbol *, int);
	int get(Symbol *);
	void clear();
};
