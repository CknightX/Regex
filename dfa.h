#ifndef _DFA_H
#define _DFA_H
#include "nfa.h"
#include <vector>
#include<queue>
#include<set>
using namespace std;


class DFA_Status
{
public:
	DFA_Status():IsFinal(false){}
	DFA_Status(Status* status):IsFinal(false){ add_nfa(status); } //�Ե���NFA״̬����DFA״̬
	set<Status*> status_set; //��ӦNFA��״̬
	void add_nfa(Status* status){ status_set.insert(status); if (status->IsFinal)IsFinal = true; } //����NFA״̬
	bool IsFinal;
};
class DFA_Edge
{
public:
	DFA_Edge(DFA_Status* b, _MatchContent content, DFA_Status* e) :Begin(b), MatchContent(content), End(e){}
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
	void _test(){ cout << AllEdges.size() <<endl<< AllStatus.size(); }
	void constructDFA(NFA& nfa);
	vector<DFA_Edge*> AllEdges;
	vector<DFA_Status*> AllStatus;
	 
};

DFA_Edge* make_edge(DFA_Status* b, _MatchContent content, DFA_Status* e);
int is_status_exist(DFA_Status* dfa_status, vector<DFA_Status*>& d); //��d����Ѱ�Ƿ���dfa_status�Ĵ��ڣ�ע��DFA״̬�������ָ���������е�NFA״̬һ�£�
bool is_dfa_status_equal(const DFA_Status* status1,const  DFA_Status* status2);


#endif