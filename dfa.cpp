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
	queue<StateSet> L; //δ�������NFA״̬
	vector<StateSet> D;//�Ѿ����ڵ�DFA״̬
	StateSet tmp;
	tmp.add_state(nfa.start_status); 
	L.push(tmp); //�Ƚ�start_status�������L
	D.push_back(tmp);
	while (!L.empty())
	{
		auto head = L.front();
		L.pop();
		vector<pair<_MatchContent, StateSet> > Map;  //��ƥ�����ݣ�״̬���Ϲ��ɵ�pair
		for (auto state : head.Set) //���ڶ���ͷ����״̬�����е�ÿһ��״̬
		{
			for (auto edge : state->OutEdges) //����״̬��ÿһ������
			{
				auto iter = Map.begin();
				if ((iter = find_if(Map.begin(), Map.end(), [&](pair<_MatchContent, StateSet>& p){return p.first == edge->MatchContent; })) != Map.end())
					(*iter).second.add_state(edge->End); //����ñ߶�Ӧ��pair�Ѿ����ڣ���ֱ�ӽ�״̬���뵽״̬������
				else //�������򴴽�һ���µ�pair
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
			if (iter != D.end()) //D���Ѿ��д�״̬����
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
	queue<Status*> L; //δ�������NFA״̬
	vector<Status*> D;//�Ѿ����ڵ�DFA״̬
	L.push(nfa.start_status); //���뿪ʼ״̬
	D.push_back(nfa.start_status);
	//AllStatus.push_back(nfa.start_status);
	while (!L.empty())
	{
		Status* head = L.front();
		L.pop();
		vector<pair<_MatchContent, Status*> > Map;  //��ƥ�����ݣ�״̬���Ϲ��ɵ�pair
		for (auto edge : head->OutEdges)
		{
			auto iter = find_if(DFAEdges.begin(), DFAEdges.end(), [&](Edge* e){return e->Start == edge->Start&&e->MatchContent == edge->MatchContent; });
			if (iter != DFAEdges.end())
			{
				for (auto e : edge->End->OutEdges) //���ظ�״̬�ĳ��߸��Ƶ��Ѿ����ڵ�DFA״̬��
					(*iter)->End->OutEdges.push_back(e);

					//ɾ���ظ�״̬
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