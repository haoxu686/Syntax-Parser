#pragma once

#include <vector>

#include "Project.h"
#include "Edge.h"

using namespace std;

class State
{
private:
	vector<set<int> *> * pvAcceptedSets;
	vector<set<int> *> * pvCascadeSets;
	vector<Project *> * pvProjects;
	Edge * pNextEdge;
	int index;
public:
	State(int);
	~State(void);
	void addToAcceptedSet(int, int);
	void addToCascadeSet(int, int);
	void addToAcceptedSet(int, set<int>::iterator, set<int>::iterator);
	set<int> * getAcceptedSetAt(int);
	set<int> * getCascadeSetsAt(int);
	void addProject(Project *);
	void setNextEdge(Edge *);
	void setIndex(int);
	bool equals(State *);
	void commit();
	static bool sortMethod(Project *, Project *);
	Edge * nextEdge();
	int getProjectCount();
	Project * getProject(int);
	int getIndex();
};
