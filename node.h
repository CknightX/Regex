#ifndef _NODE_H
#define _NODE_H
#include<vector>
using namespace std;
class Node
{
public:
	enum TYPE{ CHAR, RANGE,AND, OR, REPEAT_0, REPEAT_1 };
	TYPE type;
	Node(TYPE _type) :type(_type){}
	virtual ~Node() = 0{}
};

typedef vector<Node*> node_pool;

class Char_Node :public Node
{
public:
	Char_Node(char _c) :Node(CHAR), c(_c){}
	~Char_Node(){}
	char c;
};
class Range_Node :public Node
{
public:
	Range_Node(int _i, int _j) :Node(RANGE),i(_i), j(_j){}
	~Range_Node(){}
	int i, j;
};

class And_Node :public Node
{
public:
	And_Node(node_pool* _pool) :Node(AND), pool(_pool){}
	~And_Node()
	{
		for (auto node : *(pool))
			delete node;
	}
	node_pool* pool;
};

class Or_Node :public Node
{
public:
	Or_Node(node_pool* _pool) :Node(OR), pool(_pool){}
	~Or_Node()
	{
		for (auto node : *(pool))
			delete node;
	}
	node_pool* pool;
};

class Repeat_Node :public Node
{
public:
	Repeat_Node(Node* _node, TYPE type) :Node(type), node(_node){}
	~Repeat_Node()
	{
		delete node;
	}
	Node* node; //÷ÿ∏¥∂‘œÛ
};
#endif