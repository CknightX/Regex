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
		vector<pair<_MatchContent, StateSet> > Map;
		for (auto state : head.Set)
		{
			for (auto edge : state->OutEdges)
			{
				auto iter = Map.begin();
				if ((iter = find_if(Map.begin(), Map.end(), [&](pair<_MatchContent, StateSet>& p){return p.first == edge->MatchContent; })) != Map.end())
					(*iter).second.add_state(edge->End);
				else
				{
					StateSet _set;
					tmp.add_state(edge->End);
					auto tmp = make_pair(edge->MatchContent, _set);
					Map.push_back(tmp);
				}
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