#pragma once

#include <string>

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();

	std::string toString() const;

	bool operator<(const Point& p);
	bool operator>(const Point& p) { return !operator<(p); }

public:
	int x;
	int y;
};

struct ComparePoint
{
	int x;
	int y;
	ComparePoint(const Point& point) : x(point.x), y(point.y) {}

	bool operator()(const Point& point)
	{
		return (point.x == x) && (point.y == y);
	}
};