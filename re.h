#ifndef _RE_H
#define _RE_H
#include<string>
#include "parser.h"
#include "nfa.h"
#include "dfa.h"
#include "state_list.h"
class Re
{
public:
	Re(Parser& parser) :nfa(parser.GenTree()), dfa(nfa), state_list(dfa),curr_index(0){}
	string match(const string& source);
	string match_all(const string& source);
private:
	NFA nfa;
	DFA dfa;
	State_List state_list;
	int curr_index;
};
#endif