#include "parser.h"


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
		Node* or_node = DealOr();
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
		char c = GetChar();
		GetChar(); //-
		char d = GetChar();
		GetChar(); //]
		return new Range_Node(c, d);
	}
	else if (curr == '\\')
	{
		char c = GetChar(); // \w \d
		switch (c)
		{
		case 'w':
			return new Range_Node('A', 'z');
			break;
		case 'd':
			return new Range_Node('0', '9');
			break;
		case '(':
			return new Range_Node('(', '(');
			break;
		case ')':
			return new Range_Node(')', ')');
			break;
		case '.':
			return new Range_Node('.', '.');
			break;
		default:
			throw;
		}
	}
	else if (curr == '.')
	{
		return new Range_Node(1, 255);
	}
	else //¹Ì¶¨×Ö·û
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
	else if (curr == '*')
	{
		return new Repeat_Node(unit_node, Node::REPEAT_0);
	}
	else if (curr == '{')
	{
		char c;
		int sum = 0;
		while ((c = GetChar()) != '}')
			sum = 10 * sum + (c - '0');
		auto pool = new node_pool;
		for (int i = 0; i < sum; ++i)
		{
			pool->push_back(unit_node);
		}
		return new And_Node(pool);
	}
	if (curr != -1)
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