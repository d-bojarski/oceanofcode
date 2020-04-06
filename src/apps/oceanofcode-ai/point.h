#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point();

	bool operator<(const Point& p);
	bool operator>(const Point& p) { return !operator<(p); }

public:
	int x;
	int y;
};

