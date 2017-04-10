#ifndef _NFA_H
#define _NFA_H
#include "parser.h"
#include<algorithm>
#include<utility>
using namespace std;
struct _MatchContent
{
	_MatchContent(int l, int r) :left(l), right(r){}
	int left, right; //Æ¥ÅäµÄ×óÓÒ±ß½ç
};

class Status;
class Edge
{
public:
	Edge(Status* s, _MatchContent m ,Status* e) :Start(s), End(e), MatchContent(m){}
	~Edge();
	_MatchContent MatchContent;
	Status* Start;
	Status* End;
};

class Status
{
public:
	Status(bool _is=false) :IsFinal(_is){}
	~Status();
	vector<Edge*> InEdges;
	vector<Edge*> OutEdges;
	bool IsFinal;

};




class NFA
{
public:
	NFA(Node* tree);
	~NFA();
private:
	pair<Status*,Status*> gen_status(Node* node);
	pair<Status*, Status*> gen_and(Node* node);
	pair<Status*, Status*> gen_or(Node* node);
	pair<Status*, Status*> gen_char(Node* node);
	pair<Status*, Status*> gen_range(Node* node);
	pair<Status*, Status*> gen_repeat_0(Node* node);
	pair<Status*, Status*> gen_repeat_1(Node* node);

	Edge* make_edge(Status* status1, _MatchContent content, Status* status2);
	Edge* make_edge(Status* status1, Status* status2);

	vector<Edge*> AllEdges;
	vector<Status*> AllStatus;
	bool _isStatusExist(Status*s){ return !(find(AllStatus.begin(), AllStatus.end(), s)==AllStatus.end()); }
	void add_edge(Edge* edge){ AllEdges.push_back(edge); }
	void add_status(Status* s){ AllStatus.push_back(s); }

	void eraseE();
	void nfa2dfa();
};
#endif