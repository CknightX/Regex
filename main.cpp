#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include <algorithm>
#include "nfa.h"
#include "dfa.h"
#include "state_list.h"
#include "re.h"
using namespace std;


int main()
{
	//Parser a("a|b"); //(ab.+)*|a*
	Parser a("[0-9]+");
	NFA b(a.GenTree());
	DFA c(b);
	State_List d(c);

	Re g("[0-9]+");
	cout<<g.match_all("d192.168.1.13wqd");
	cin.get();
	return 0;
}