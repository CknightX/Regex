#ifndef _NFA_H
#define _NFA_H
#include "parser.h"
#include<algorithm>
#include<utility>
using namespace std;
struct _MatchContent
{
	_MatchContent(int l, int r) :left(l), right(r){}
	int left, right; //匹配的左右边界
	bool operator==(const _MatchContent& m){ return left == m.left&&right == m.right; }
};

class Status;
class Edge
{
public:
	Edge(Status* s, _MatchContent m ,Status* e) :Start(s), End(e), MatchContent(m){}
	~Edge(){} //释放边并不释放其起点和终点
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

public:
	//pair中的指针分别为该子图的start和end
	pair<Status*, Status*> gen_status(Node* node);
	pair<Status*, Status*> gen_and(Node* node);
	pair<Status*, Status*> gen_or(Node* node);
	pair<Status*, Status*> gen_char(Node* node);
	pair<Status*, Status*> gen_range(Node* node);
	pair<Status*, Status*> gen_repeat_0(Node* node);
	pair<Status*, Status*> gen_repeat_1(Node* node);

	Status* start_status;
	Status* end_status;

	Edge* make_edge(Status* status1, _MatchContent content, Status* status2, bool isAdd = true);
	Edge* make_edge(Status* status1, Status* status2, bool isAdd = true);

	vector<Edge*> AllEdges; //考虑替换为map，提高效率。map<Status*,Edge_link>
	vector<Status*> AllStatus;

	bool _isStatusExist(Status*s){ return !(find(AllStatus.begin(), AllStatus.end(), s) == AllStatus.end()); } //状态是否存在
	bool _isEedge(Edge* edge){ return (edge->MatchContent.left == -1); } //是否为E边
	bool _isValidStatus(Status* s);

	void add_edge(Edge* edge){ AllEdges.push_back(edge); edge->Start->OutEdges.push_back(edge); edge->End->InEdges.push_back(edge); }
	void add_status(Status* s){ AllStatus.push_back(s); }
	void set_edge_E(Edge* edge){ edge->MatchContent.left = edge->MatchContent.right = -1; }
	void destroy_edge(Edge* edge)
	{
		edge->Start->OutEdges.erase(find(edge->Start->OutEdges.begin(), edge->Start->OutEdges.end(), edge)); //删除起点的出边
		edge->End->InEdges.erase(find(edge->End->InEdges.begin(), edge->End->InEdges.end(), edge)); //删除终点的出边
		delete edge; //释放内存
		//注意，此时还未从AllEdge中删除此边
	}

	void eraseE();
	void E2NFA();
	void find_end_status();
};
#endif