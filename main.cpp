#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include <algorithm>
#include "nfa.h"
#include "dfa.h"
using namespace std;


int main()
{
	Parser a("abc(a|b|c)*cba"); //(ab.+)*|a*
	//Parser a("a|bc"); //(ab.+)*|a*
	auto b = a.GenTree();
	NFA c(b);
	DFA d(c);
	d._test();
	cin.get();
	return 0;
}