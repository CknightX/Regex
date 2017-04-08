#ifndef _PARSER_H
#define _PARSER_H
#include<iostream>
#include<vector>
using namespace std;
class Node
{
public:
	enum TYPE{ CHAR,AND, OR, REPEAT_0, REPEAT_1 };
	TYPE type;
	Node(TYPE _type) :type(_type){}
	virtual ~Node() = 0{}
};

typedef vector<Node*> node_pool;

class Char_Node:public Node
{
public:
	Char_Node(char _c) :Node(CHAR),c(_c){}
	~Char_Node(){}
protected:
	char c;
};
class And_Node :public Node
{
public:
	And_Node(node_pool* _pool) :Node(AND),pool(_pool){}
	~And_Node()
	{
		for (auto node : *(pool))
			delete node;
	}
protected:
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
protected:
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
protected:
	Node* node; //重复对象
};

class Parser
{
public:
	Parser(const string s) :reg(s){}
	Node* GenTree(){return (Tree=DealOr()); }
	Node* GetTree(){ return Tree; }
	~Parser(){ Deallocate(); }
private:
	string reg;
	size_t index;
	char curr;
	Node* Tree;
	int GetChar(){ if (index < reg.size()){ curr = reg[index++]; } else curr = -1; return curr; }
	void Throw_Char(){ --index; }
	int LookChar(){ auto c = GetChar(); if (c != -1)Throw_Char(); return c; }
	Node* DealChar();
	Node* DealUnit();
	Node* DealAnd();
	Node* DealOr();
	Node* DealBlock();
	void Deallocate();
};

Node* Parser::DealChar()
{
	GetChar();
	if (curr == -1)
		return nullptr;
	return new Char_Node(curr);
}

Node* Parser::DealUnit()
{
	GetChar();
	if (curr == -1)
		return nullptr;
	if (curr == '(')
	{
		Node* or_node=DealOr();
		GetChar(); //)
		return or_node;
	}
	else if (curr == ')')
	{
		Throw_Char();
		return nullptr;
	}
	else if (curr == '[')
	{

	}
	else if (curr == '{')
	{

	}
	else if (curr == '\\')
	{

	}
	else //固定字符
	{
		return new Char_Node(curr);
	}
	return nullptr;
}

Node* Parser::DealBlock()
{
	Node* unit_node = DealUnit();
	GetChar();
	if (curr == '+')
	{
		return new Repeat_Node(unit_node, Node::REPEAT_1);
	}
	if (curr == '*')
	{
		return new Repeat_Node(unit_node, Node::REPEAT_0);
	}
	if (curr!=-1)
		Throw_Char();
	return unit_node;
}

Node* Parser::DealAnd()
{
	node_pool* pool = new node_pool;
	while (true)
	{
		Node* block = DealBlock();
		if (!block)
			break;

		pool->push_back(block);

		if (LookChar() == '|')
			break;

	}
	if (pool->empty())
	{
		delete pool;
		return nullptr;
	}
	else if (pool->size() == 1)
	{
		Node* tmp = *(pool->begin());
		delete pool;
		return tmp;
	}
	else
	{
		return new And_Node(pool);
	}
}

Node* Parser::DealOr()
{
	node_pool* pool = new node_pool;
	while (true)
	{
		Node* and_node = DealAnd();
		if (!and_node)
			break;

		pool->push_back(and_node);

		if (LookChar() != '|')
			break;
		else
			GetChar(); //eat |
	}
	if (pool->empty())
	{
		delete pool;
		return nullptr;
	}
	else if (pool->size() == 1)
	{
		Node* tmp = *(pool->begin());
		delete pool;
		return tmp;
	}
	else
	{
		return new Or_Node(pool);
	}
}

void Parser::Deallocate()
{
	delete Tree;
}
#endif