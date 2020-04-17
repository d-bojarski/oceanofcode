#include "gridgenerator.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <array>

#include <qregexp.h>

GridGenerator::GridGenerator(int gridSize) :
	gridSize(gridSize),
	seed(0),
	grid(),
	tiles()
{
}

GridGenerator::~GridGenerator()
{
}

void GridGenerator::generate()
{
	Grid result;
	result.width = gridSize;
	result.height = gridSize;
	result.initialize();

	if (seed != 0)
	{
		std::srand(seed);
	}
	else
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}
	std::rand();

	int max = 5 + std::rand() / ((RAND_MAX + 1u) / 26);
	// Create random islands.
	for (int i = 0; i < max; i++)
	{

		int x = std::rand() / ((RAND_MAX + 1u) / 15);
		int y = std::rand() / ((RAND_MAX + 1u) / 15);

		result[y][x] = 1;
	}

	grid = result;

	// increase the island tiles
	for (int y = 0; y < gridSize; y++)
	{
		for (int x = 0; x < gridSize; x++)
		{
			if (result[y][x])
			{
				if (x - 1 >= 0)
				{
					grid[y][x - 1] = 1;
				}

				if (y + 1 < gridSize)
				{
					grid[y + 1][x] = 1;

					if (x - 1 >= 0)
					{
						grid[y + 1][x - 1] = 1;
					}
				}
			}
		}
	}

	do
	{
		tiles = generateTiles(grid);
	} while (tiles.empty());
}


std::vector<Tile> GridGenerator::generateTiles(Grid& grid)
{
	std::array<QString, 13> tiles = {
		"11.0.111",
		".11111.0",
		".0.0.111",
		"11.0.0.1",
		".111.0.0",
		".0.111.0",
		"1111.0.1",
		".0.11111",
		"11111111",
		"11111101",
		"11110111",
		"11011111",
		"01111111"
	};

	std::vector<Tile> tileSprites;
	bool stop = false;

	for (int y = 0; y < gridSize && !stop; y++)
	{
		for (int x = 0; x < gridSize && !stop; x++)
		{
			bool island = (grid[y][x] == 1);

			if (!island)
			{
				continue;
			}

			// Create tile.
			QString tile;
			tile.append(x - 1 < 0 || y - 1 < 0 || grid[y - 1][x - 1] ? "1" : "0");
			tile.append(x - 1 < 0 || grid[y][x - 1] ? "1" : "0");
			tile.append(x - 1 < 0 || y + 1 >= gridSize || grid[y + 1][x - 1] ? "1" : "0");
			tile.append(y + 1 >= gridSize || grid[y + 1][x] ? "1" : "0");
			tile.append(x + 1 >= gridSize || y + 1 >= gridSize || grid[y + 1][x + 1] ? "1" : "0");
			tile.append(x + 1 >= gridSize || grid[y][x + 1] ? "1" : "0");
			tile.append(x + 1 >= gridSize || y - 1 < 0 || grid[y - 1][x + 1] ? "1" : "0");
			tile.append(y - 1 < 0 || grid[y - 1][x] ? "1" : "0");

			QString sprite;
			for (int i = 0; i < tiles.size(); i++)
			{
				if (tile.contains(QRegExp(tiles[i])))
				{
					QString tile = tiles[i];
					tile = tile.replace(".", "x");

					sprite = tile + ".png";
					tileSprites.push_back({ y, x, sprite });
					break;
				}
			}

			if (sprite.isEmpty())
			{
				// fix error
				grid[std::max(y - 1, 0)][std::max(0, x - 1)] = 1;
				grid[y][std::max(0, x - 1)] = 1;
				grid[std::min(y + 1, gridSize - 1)][std::max(0, x - 1)] = 1;
				grid[std::max(y - 1, 0)][std::max(0, x)] = 1;
				grid[std::min(y + 1, gridSize - 1)][std::max(0, x)] = 1;
				grid[std::max(y - 1, 0)][std::min(x + 1, gridSize - 1)] = 1;
				grid[y][std::min(x + 1, gridSize - 1)] = 1;
				grid[std::min(y + 1, gridSize - 1)][std::min(x + 1, gridSize - 1)] = 1;

				tileSprites.clear();
				stop = true;
			}
		}
	}

	if (!stop)
	{
		// Java source code use another coordinate system.
		grid.inverse();
	}

	return tileSprites;
}