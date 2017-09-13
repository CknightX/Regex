#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include <algorithm>
#include "re.h"
using namespace std;


int main()
{
	Re g("((aa|bb)|((ab|ba)(aa|bb)*(ab|ba)))*"); //匹配偶数个a和偶数个b
	cout<<g.match("a")<<endl;
	cout<<g.match("ab")<<endl;
	cout<<g.match("aa")<<endl;
	cout<<g.match("bb")<<endl;
	cout<<g.match("abab")<<endl;
	cout<<g.match("aaabbbb")<<endl;
	cout<<g.match("abbbba")<<endl;
	cout<<g.match("aaaaabbbb")<<endl;
	cout<<g.match("ababababab")<<endl;
	cout<<g.match("babababababa")<<endl;
	cin.get();
	return 0;
}