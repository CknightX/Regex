#include "dfa.h"
#include<queue>
using namespace std;
bool StateSet::operator==(const StateSet& _set)
{
	if (Set.size() != _set.Set.size())
		return false;
	auto b1 = Set.begin();
	auto b2 = _set.Set.begin();
	for (; b1 != Set.end(); ++b1, ++b2)
	{
		if ((*b1) != (*b2))return false;
	}
	return true;
}
void DFA::constructDFA(NFA& nfa)
{
	/*
	queue<StateSet> L; //未被处理的NFA状态
	vector<StateSet> D;//已经存在的DFA状态
	StateSet tmp;
	tmp.add_state(nfa.start_status); 
	L.push(tmp); //先将start_status加入队列L
	D.push_back(tmp);
	while (!L.empty())
	{
		auto head = L.front();
		L.pop();
		vector<pair<_MatchContent, StateSet> > Map;  //由匹配内容，状态集合构成的pair
		for (auto state : head.Set) //对于队列头部的状态集合中的每一个状态
		{
			for (auto edge : state->OutEdges) //对于状态的每一条出边
			{
				auto iter = Map.begin();
				if ((iter = find_if(Map.begin(), Map.end(), [&](pair<_MatchContent, StateSet>& p){return p.first == edge->MatchContent; })) != Map.end())
					(*iter).second.add_state(edge->End); //如果该边对应的pair已经存在，则直接将状态加入到状态集合中
				else //不存在则创建一个新的pair
				{
					StateSet _set;
					tmp.add_state(edge->End);
					auto tmp = make_pair(edge->MatchContent, _set);
					Map.push_back(tmp);
				}
			}
		} 
		for (auto m : Map)
		{
			auto iter = find(D.begin(), D.end(), m.second);
			if (iter != D.end()) //D中已经有此状态集合
			{
				make_edge(Set2Status(head), m.first, Set2Status(*iter));
			}
			else
			{
				D.push_back(m.second);
				make_edge(Set2Status(head), m.first, Set2Status(*(D.rbegin())));
			}
		}


	}
	*/
	queue<Status*> L; //未被处理的NFA状态
	vector<Status*> D;//已经存在的DFA状态
	L.push(nfa.start_status); //加入开始状态
	D.push_back(nfa.start_status);
	//AllStatus.push_back(nfa.start_status);
	while (!L.empty())
	{
		Status* head = L.front();
		L.pop();
		vector<pair<_MatchContent, Status*> > Map;  //由匹配内容，状态集合构成的pair
		for (auto edge : head->OutEdges)
		{
			auto iter = find_if(DFAEdges.begin(), DFAEdges.end(), [&](Edge* e){return e->Start == edge->Start&&e->MatchContent == edge->MatchContent; });
			if (iter != DFAEdges.end())
			{
				for (auto e : edge->End->OutEdges) //将重复状态的出边复制到已经存在的DFA状态上
					(*iter)->End->OutEdges.push_back(e);

					//删除重复状态
					nfa.destroy_edge(edge);
					nfa.AllStatus.erase(find(nfa.AllStatus.begin(), nfa.AllStatus.end(), edge));
			}
			

		}
	}
}
DFA_Status* Set2Status(const StateSet& _set)
{
	DFA_Status* dfa_status = new DFA_Status;
	for (auto nfa_status : _set.Set)
	{
		for (auto nfa_edge : nfa_status->OutEdges) 
		{
			dfa_status->OutEdges.push_back(nfa_edge);
		}
	}
	return dfa_status;
}
Edge* make_edge(Status* b, _MatchContent content, Status* e)
{
	return new Edge(b,content,e);
}