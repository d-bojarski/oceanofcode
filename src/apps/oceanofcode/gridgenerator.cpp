#include "gridgenerator.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <array>

#include <qregexp.h>

GridGenerator::GridGenerator(int gridSize) :
	gridSize(gridSize)
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

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::rand();

	int max = 5 + std::rand() / ((RAND_MAX + 1u) / 26);
	// Create random islands.
	for (int i = 0; i < max; i++) {

		int x = std::rand() / ((RAND_MAX + 1u) / 15);
		int y = std::rand() / ((RAND_MAX + 1u) / 15);

		result[x][y] = 1;
	}

	grid = result;

	// increase the island tiles
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			if (result[x][y])
			{
				if (y - 1 >= 0)
				{
					grid[x][y - 1] = 1;
				}

				if (x + 1 < gridSize)
				{
					grid[x + 1][y] = 1;

					if (y - 1 >= 0)
					{
						grid[x + 1][y - 1] = 1;
					}
				}
			}
		}
	}

	do {
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

	for (int x = 0; x < gridSize && !stop; x++)
	{
		for (int y = 0; y < gridSize && !stop; y++)
		{
			bool island = (grid[x][y] == 1);

			if (!island)
			{
				continue;
			}

			// Create tile.
			QString tile;
			tile.append(y - 1 < 0 || x - 1 < 0 || grid[x - 1][y - 1] ? "1" : "0");
			tile.append(y - 1 < 0 || grid[x][y - 1] ? "1" : "0");
			tile.append(y - 1 < 0 || x + 1 >= gridSize || grid[x + 1][y - 1] ? "1" : "0");
			tile.append(x + 1 >= gridSize || grid[x + 1][y] ? "1" : "0");
			tile.append(y + 1 >= gridSize || x + 1 >= gridSize || grid[x + 1][y + 1] ? "1" : "0");
			tile.append(y + 1 >= gridSize || grid[x][y + 1] ? "1" : "0");
			tile.append(y + 1 >= gridSize || x - 1 < 0 || grid[x - 1][y + 1] ? "1" : "0");
			tile.append(x - 1 < 0 || grid[x - 1][y] ? "1" : "0");

			QString sprite;
			for (int i = 0; i < tiles.size(); i++)
			{
				if (tile.contains(QRegExp(tiles[i])))
				{
					QString tile = tiles[i];
					tile = tile.replace(".", "x");

					sprite = tile + ".png";
					tileSprites.push_back({ x, y, sprite });
					break;
				}
			}

			if (sprite.isEmpty())
			{
				// fix error
				grid[std::max(x - 1, 0)][std::max(0, y - 1)] = 1;
				grid[x][std::max(0, y - 1)] = 1;
				grid[std::min(x + 1, gridSize - 1)][std::max(0, y - 1)] = 1;
				grid[std::max(x - 1, 0)][std::max(0, y)] = 1;
				grid[std::min(x + 1, gridSize - 1)][std::max(0, y)] = 1;
				grid[std::max(x - 1, 0)][std::min(y + 1, gridSize - 1)] = 1;
				grid[x][std::min(y + 1, gridSize - 1)] = 1;
				grid[std::min(x + 1, gridSize - 1)][std::min(y + 1, gridSize - 1)] = 1;

				tileSprites.clear();
				stop = true;
			}
		}
	}

	return tileSprites;
}