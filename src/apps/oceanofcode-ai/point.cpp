#include "point.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Point::Point() :
	Point(-1,-1)
{
}

Point::Point(int x, int y) :
	x(x),
	y(y)
{

}

Point::~Point()
{
}

std::string Point::toString() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------

bool Point::operator<(const Point& p)
{
	return x < p.x && y < p.y;
}