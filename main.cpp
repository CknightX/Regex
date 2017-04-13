#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include <algorithm>
#include "nfa.h"
using namespace std;


int main()
{
	Parser a("(ab|cd)*"); //(ab.+)*|a*
	auto b = a.GenTree();
	NFA c(b);

	cin.get();
	return 0;
}