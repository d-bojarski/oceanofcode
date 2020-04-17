#include "ai.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
AI::AI(MessageManager* _messageManager) :
	_messageManager(_messageManager),
	_stop(false),
	_me(),
	_opponent(),
	_grid()
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
	_messageManager->debug("AI::start");

	_messageManager->read(&_grid.width);
	_messageManager->read(&_grid.height);
	_messageManager->read(&_me.id);
	_messageManager->readIgnore();

	_messageManager->debug("width: " + std::to_string(_grid.width));
	_messageManager->debug("height: " + std::to_string(_grid.height));
	_messageManager->debug("_me.id: " + std::to_string(_me.id));

	_grid.initialize();

	for (int h = 0; h < _grid.height; h++)
	{
		std::string line;
		_messageManager->read(&line);
		_grid.fill(h, line);
		//messageManager->debug("line: " + std::to_string(h) + line);
	}

	calculateGridAccess();
	calculatePaths();

	_messageManager->snapshot("grid-access-" + std::to_string(_me.id), _gridAccess);
	for (int i = 0; i < _gridPaths.size(); i++)
	{
		_messageManager->snapshot("grid-path-" + std::to_string(_me.id) + "-" + std::to_string(i), _gridPaths.at(i));
	}

	_messageManager->send("7 7");

	bool run = true;
	// game loop
	do
	{
#ifdef LIBRARY
		_mutex.lock();
		run = !_stop;
		_mutex.unlock();
#endif

		//_messageManager->debug("run " + std::string(run ? "true" : "false"));
		run = run && _messageManager->read(&_me.x);
		run = run && _messageManager->read(&_me.y);
		run = run && _messageManager->read(&_me.life);
		run = run && _messageManager->read(&_opponent.life);
		run = run && _messageManager->read(&_me.torpedoCooldown);
		run = run && _messageManager->read(&_me.sonarCooldown);
		run = run && _messageManager->read(&_me.silenceCooldown);
		run = run && _messageManager->read(&_me.mineCooldown);
		_messageManager->readIgnore();


		std::string sonarResult;
		run = run && _messageManager->read(&sonarResult);
		_messageManager->readIgnore();

		std::string opponentOrders;
		run = run && _messageManager->read(&opponentOrders);

		// TODO use sonar
		//std::cerr << "sonarResult" << sonarResult << std::endl;

		// TODO use opponent orders
		//std::cerr << "opponentOrders" << opponentOrders << std::endl;



		//_messageManager->snapshot("gridAccess" + std::to_string(_me.id), gridAccess);

		if (run)
		{
			_messageManager->send("MOVE N TORPEDO");
		}
	} while (run);
	_messageManager->debug("AI stopped.");
}

void AI::stop()
{
#ifdef LIBRARY
	_mutex.lock();
	_stop = true;
	_mutex.unlock();
#endif
}

void AI::calculateGridAccess()
{
	_gridAccess.emptyCopy(_grid);

	for (int h = 0; h < _grid.height; h++)
	{
		for (int w = 0; w < _grid.width; w++)
		{
			int access = 0;
			if (_grid[h][w] == 0)
			{
				access += ((h > 0) && (_grid[h - 1][w] == 0)) ? 1 : 0;
				access += ((h < _grid.height - 1) && (_grid[h + 1][w] == 0)) ? 1 : 0;
				access += ((w > 0) && (_grid[h][w - 1] == 0)) ? 1 : 0;
				access += ((w < _grid.width - 1) && (_grid[h][w + 1] == 0)) ? 1 : 0;
			}
			_gridAccess[h][w] = access;
		}
	}
}

void AI::calculatePaths()
{
	Grid grid;
	grid.emptyCopy(_grid);

	int group = 1;
	for (int y = 0; y < _grid.height; y++)
	{
		for (int x = 0; x < _grid.width; x++)
		{
			if (calculatePaths(grid, group, x, y) > 0)
			{
				group++;
			}
		}
	}
	_gridPaths.push_back(grid);
}

int AI::calculatePaths(Grid& grid, int group, int x, int y)
{
	int boxCount = 0;
	if (grid[y][x] == 0 && _gridAccess[y][x] > 0)
	{
		grid[y][x] = group;
		boxCount++;

		if (y > 0)
		{
			// Left box.
			boxCount += calculatePaths(grid, group, x, y - 1);
		}
		if (x > 0)
		{
			// Right box.
			boxCount += calculatePaths(grid, group, x - 1, y);
		}
		if (y < grid.height - 1)
		{
			// Top box.
			boxCount += calculatePaths(grid, group, x, y + 1);
		}
		if (x < grid.width - 1)
		{
			// Top box.
			boxCount += calculatePaths(grid, group, x + 1, y);
		}
	}
	return boxCount;
}

void AI::calculateUnreachablePath()
{
}

void AI::calculateOptimalPath()
{
	// Maximum path without SURFACE.
	// Maximum path without receive torpedo (opponent discover position).
	// SURFACE close to the sector boundary.

	// Biggest motif x9
}
