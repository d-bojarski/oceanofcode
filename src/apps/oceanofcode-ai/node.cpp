#include "node.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Node::Node() :
	Node(-1,-1)
{
}

Node::Node(int x, int y) :
	x(x),
	y(y)
{
}

Node::~Node()
{
	nodes.clear();
}

Point Node::toPoint() const
{
	return Point(x, y);
}

std::string Node::toString() const
{
	std::string result = Point(x, y).toString() + ": ";
	for (size_t i = 0; i < nodes.size(); i++)
	{
		result += nodes.at(i)->toPoint().toString() + " ";
	}
	return result;
}
