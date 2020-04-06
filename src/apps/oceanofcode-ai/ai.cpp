#include "ai.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
AI::AI() :
	me(),
	opponent(),
	grid()
{
}

AI::~AI()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------
void AI::start()
{
	std::cin >> grid.width;
	std::cin >> grid.height;
	std::cin >> me.id;
	std::cin.ignore();

	grid.initialize();

	for (int h = 0; h < grid.height; h++)
	{
		std::string line;
		std::getline(std::cin, line);
		fill(grid[h], line);
	}
	grid.show();

	calculateGridAccess();

	grid.show();

	std::cout << "7 7" << std::endl;

	// game loop
	while (1)
	{
		std::cin >> me.x;
		std::cin >> me.y;
		std::cin >> me.life;
		std::cin >> opponent.life;
		std::cin >> me.torpedoCooldown;
		std::cin >> me.sonarCooldown;
		std::cin >> me.silenceCooldown;
		std::cin >> me.mineCooldown;
		std::cin.ignore();


		std::string sonarResult;
		std::cin >> sonarResult;
		std::cin.ignore();
		std::string opponentOrders;
		std::getline(std::cin, opponentOrders);

		// TODO use sonar
		//std::cerr << "sonarResult" << sonarResult << std::endl;

		// TODO use opponent orders
		//std::cerr << "opponentOrders" << opponentOrders << std::endl;







		std::cout << "MOVE N TORPEDO" << std::endl;
	}
}

void AI::fill(short* line, const std::string& lineValue)
{
	for (int w = 0; w < lineValue.size(); w++)
	{
		line[w] = (lineValue.at(w) == 'x') ? 1 : 0;
	}
}

void AI::calculateGridAccess()
{
	gridAccess.emptyCopy(grid);
	//gridAccess.reverse();

	for (int h = 0; h < grid.height; h++)
	{
		for (int w = 0; w < grid.width; w++)
		{
			int access = 0;
			if (h > 0 && grid[h - 1][w] == 0)
			{
				access++;
			}
			if (h < grid.height && grid[h + 1][w] == 0)
			{
				access++;
			}

			if (w > 0 && grid[h][w - 1] == 0)
			{
				access++;
			}
			if (w < grid.width && grid[h][w + 1] == 0)
			{
				access++;
			}

			gridAccess[h][w] = (access > 1) ? access : 0;
		}
	}
}

void AI::calculateOptimalPath()
{
	// Maximum path without SURFACE.
	// Maximum path without receive torpedo (opponent discover position).
	// SURFACE close to the sector boundary.

	// Biggest motif x9
}
