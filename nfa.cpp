#include "nfa.h"
NFA::NFA(Node* Tree)
{
	gen_status(Tree);
}
NFA::~NFA()
{

}
pair<Status*, Status*> NFA::gen_status(Node* node)
{
	pair<Status*, Status*> status;
	switch (node->type)
	{
	case Node::CHAR:
		status = gen_char(node);
		break;
	case Node::AND:
		status = gen_and(node);
		break;
	case Node::OR:
		status = gen_or(node);
		break;
	case Node::REPEAT_0:
		status = gen_repeat_0(node);
		break;
	case Node::REPEAT_1:
		status = gen_repeat_1(node);
		break;
	default:
		break;
	}
	return status;
}
pair<Status*, Status*> NFA::gen_repeat_0(Node* node)
{
	Repeat_Node* repeat_node = static_cast<Repeat_Node*>(node);
	Status* s_start = new Status;
	Status* s_end = s_start;
	Status* _s_start = new Status;
	Status* _s_end = new Status;
	pair<Status*, Status*> s_child = gen_status(repeat_node->node);
	make_edge(_s_start, s_child.first);
	make_edge(s_child.second, _s_end);
	make_edge(s_start, _s_start);
	make_edge(_s_end, s_end);
	return make_pair(s_start, s_end);

}
pair<Status*, Status*> NFA::gen_repeat_1(Node* node)
{
	Repeat_Node* repeat_node = static_cast<Repeat_Node*>(node);
	Status* s_start = new Status;
	Status* s_end = new Status(true);
	Status* _s_start = new Status;
	Status* _s_end = new Status;
	pair<Status*, Status*> s_child = gen_status(repeat_node->node);
	make_edge(s_start, s_child.first);
	make_edge(s_child.second, s_end);
	make_edge(_s_start, s_child.first);
	make_edge(s_child.second, _s_end);
	make_edge(s_end, _s_start);
	make_edge(_s_end, s_end);
	return make_pair(s_start, s_end);
}
pair<Status*, Status*> NFA::gen_and(Node* node)
{
	And_Node* and_node = static_cast<And_Node*>(node);
	Status* s_start = nullptr;
	Status* s_end = nullptr;
	for (auto s : *(and_node->pool))
	{
		auto tmp = gen_status(s);
		if (!s_end)
		{
			s_start=tmp.first;
			s_end = tmp.second;
			continue;
		}
		s_end = ((make_edge(s_end,tmp.first)))->End;
	}
	return make_pair(s_start, s_end);
}
pair<Status*, Status*> NFA::gen_or(Node* node)
{
	Or_Node* or_node = static_cast<Or_Node*>(node);
	Status* s_start = new Status;
	Status* s_end = new Status;
	for (auto s : *(or_node)->pool)
	{
		auto tmp = gen_status(s);
		make_edge(s_start, tmp.first);
		make_edge(tmp.second, s_end);
	}
	return make_pair(s_start, s_end);
}
pair<Status*, Status*> NFA::gen_char(Node* node)
{
	Char_Node* char_node = static_cast<Char_Node*>(node);
	Status* s_start = new Status;
	Status* s_end = new Status(true);
	Edge* edge = make_edge(s_start, _MatchContent(char_node->c, char_node->c), s_end);
	return make_pair(s_start,s_end);
}
pair<Status*, Status*> NFA::gen_range(Node* node)
{
	Range_Node* char_node = static_cast<Range_Node*>(node);
	Status* s_start = new Status;
	Status* s_end = new Status(true);
	Edge* edge = make_edge(s_start, _MatchContent(char_node->i, char_node->j), s_end);
	return make_pair(s_start,s_end);
}
Edge* NFA::make_edge(Status* status1, _MatchContent content, Status* status2)
{
	if (status1->IsFinal)
		status1->IsFinal = false;
	auto edge = new Edge(status1, content, status2);
	status1->OutEdges.push_back(edge);
	status2->InEdges.push_back(edge);
	if (!_isStatusExist(status1))
		add_status(status1);
	if (!_isStatusExist(status2))
		add_status(status2);
	AllEdges.push_back(edge);
	return edge;
}

Edge* NFA::make_edge(Status* status1, Status* status2)
{
	return make_edge(status1, _MatchContent(-1, -1), status2);
}

void NFA::eraseE() //消除所有E边
{

}

void NFA::nfa2dfa() //NFA转化为DFA
{

}