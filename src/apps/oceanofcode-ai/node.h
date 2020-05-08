#pragma once

#include "point.h"

#include <vector>
#include <string>

class Node
{
public:
	Node();
	Node(int x, int y);
	~Node();

	Point toPoint() const;

	std::string toString() const;
public:
	int x;
	int y;

	std::vector<Node*> nodes;
};

struct CompareNode
{
	int x;
	int y;
	CompareNode(int x, int y) : x(x), y(y) {}

	bool operator()(const Node* node)
	{
		return (node->x == x) && (node->y == y);
	}
};