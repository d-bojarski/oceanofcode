#include "ai.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
AI::AI(MessageManager* messageManager) :
	messageManager(messageManager),
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
	messageManager->debug("AI::start");
	messageManager->read(&grid.width);
	messageManager->read(&grid.height);
	messageManager->read(&me.id);
	messageManager->readIgnore();

	messageManager->debug("width: " + std::to_string(grid.width));
	messageManager->debug("height: " + std::to_string(grid.height));
	messageManager->debug("me.id: " + std::to_string(me.id));

	grid.initialize();

	for (int h = 0; h < grid.height; h++)
	{
		std::string line;
		messageManager->read(&line);
		messageManager->debug("line: " + std::to_string(h) + line);
		grid.fill(h, line);
	}
	//grid.show();

	//calculateGridAccess();

	//grid.show();

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
