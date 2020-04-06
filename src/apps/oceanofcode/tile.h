#pragma once

#include "point.h"

#include <qstring.h>

class Tile
{
public:
	Tile();
	Tile(int x, int y, const QString& imageName);

public:
	int x;
	int y;
	QString imageName;
};

struct TileComparator
{
	TileComparator(int x, int y) :
		x(x), y(y)
	{
	}

	bool operator() (const Tile& t) const
	{
		return t.x == x && t.y == y;
	};

private:
	int x;
	int y;
};