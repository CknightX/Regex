#ifndef _STATE_LIST_H
#define _STATE_LIST_H
#include "dfa.h"
#include <utility>
using namespace std;
const int MAX_CHAR = 256;
class Matrix
{
public:
	Matrix(int n) :N(n){ construct(N); }
	~Matrix(){ destruct(); }
	int get(int x, int y){ if (x >= N || y >= MAX_CHAR)throw; return matrix[x][y]; }
	int getN(){ return N; }
	void set(int value, int x, int y){ if (x >= N || y >= MAX_CHAR)throw; matrix[x][y] = value; }
	void print(){ for (int i = 0; i < N; ++i){ for (int j = 'a'; j <='z'; ++j)cout << matrix[i][j] << ' '; cout << endl;} }
	void construct(int n);
	void destruct();
private:
	int N; //½×Êý
	int** matrix;
};

class State_List
{
public:
	State_List(DFA& dfa);
	int get_status(int i, int j){ return matrix.get(i, j); }
	void _test(){ matrix.print(); }
	int get_start(){ return start_status; }
	bool is_in_end_pos(int i){ for (auto j : end_pos)if (i == j)return true; return false; }
private:
	Matrix matrix; //×´Ì¬×ªÒÆ±í
	int start_status;
	vector<int> end_pos;
};
#endif