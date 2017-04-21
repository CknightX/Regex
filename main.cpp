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
	Parser a("([a-z]|[0-9])\\.([a-z]|[0-9])"); //(ab.+)*|a*
	//Parser a("a|b"); //(ab.+)*|a*
	Re b(a);
	cout<<b.match_all("3.4sss4.3s");
	cin.get();
	return 0;
}