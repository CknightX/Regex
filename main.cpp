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
	Parser a("\\d"); //(ab.+)*|a*
	//Parser a("a|b"); //(ab.+)*|a*
	Re b(a);
	cout<<b.match("aa2babbaba");
	cin.get();
	return 0;
}