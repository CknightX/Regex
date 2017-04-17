#ifndef _DFA_H
#define _DFA_H
#include "nfa.h"
#include <vector>
#include<queue>
using namespace std;

class DFA_Status
{
public:
	vector<Edge*> OutEdges; //DFA的状态只需保留出边
	bool operator==(const DFA_Status& status);
};
class DFA_Edge
{
public:
	_MatchContent MatchContent;
	DFA_Status* Begin;
	DFA_Status* End;
};
class StateSet
{
public:
	StateSet(){}
	StateSet(const StateSet& _set){ Set.insert(Set.end(), _set.Set.begin(), _set.Set.end()); }
	~StateSet(){}
public:
	vector<Status*> Set;
	void add_state(Status* state){ Set.push_back(state); }
	bool operator==(const StateSet& _set);
	
};

class DFA
{
public:
	DFA(NFA& nfa){ constructDFA(nfa); }
	~DFA(){}
private:
	void constructDFA(NFA& nfa);
	vector<Edge*> DFAEdges;
	 
};


DFA_Edge* make_edge(Status* b, _MatchContent content, Status* e);
DFA_Status* Set2Status(const StateSet& _set); //将状态集合转化为单个状态
#endif