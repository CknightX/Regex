#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include "nfa.h"
using namespace std;


int main()
{
	
	Parser a("a*"); //(ab.+)*|a*
	auto b = a.GenTree();
	NFA c(b);
	cin.get();
	return 0;
}