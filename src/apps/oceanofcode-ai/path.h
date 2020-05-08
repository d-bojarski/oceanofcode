#pragma once

#include "point.h"

#include <vector>
#include <string>

class Path
{
public:
	Path();
	~Path();

	bool addPoint(const Point& point);
	const Point& at(int i) const;
	unsigned int size() const;

	bool contains(const Point& point);

	std::string toString();

private:
	std::vector<Point> _way;
};

