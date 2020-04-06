#pragma once

#include "grid.h"
#include "point.h"
#include "tile.h"

#include <qstring.h>
#include <vector>

class GridGenerator
{
public:
	GridGenerator(int gridSize);
	~GridGenerator();


	void generate();
	std::vector<Tile> generateTiles(Grid& grid);

public:
	const int gridSize;
	Grid grid;
	std::vector<Tile> tiles;
};

