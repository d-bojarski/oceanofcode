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
	_rootNodes.clear();
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
	_draftGrid.emptyCopy(_grid);

	for (int h = 0; h < _grid.height; h++)
	{
		std::string line;
		_messageManager->read(&line);
		_grid.fill(h, line);
		//messageManager->debug("line: " + std::to_string(h) + line);
	}

	calculateGridAccess();
	_messageManager->snapshot("grid-access-" + std::to_string(_me.id), _gridAccess);

	calculateNodes();
	_messageManager->snapshot("grid-region-" + std::to_string(_me.id), _gridRegions);


	//auto result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(0, 0));
	//_messageManager->debug((*result)->toString());
	//result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(1, 0));
	//_messageManager->debug((*result)->toString());
	//result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(2, 0));
	//_messageManager->debug((*result)->toString());
	//result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(0, 1));
	//_messageManager->debug((*result)->toString());
	//result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(1, 1));
	//_messageManager->debug((*result)->toString());
	//result = std::find_if(_nodeList.begin(), _nodeList.end(), CompareNode(2, 1));
	//_messageManager->debug((*result)->toString());


	calculatePaths();
	for (size_t i = 0; i < _paths.size(); i++)
	{
		_draftGrid.fill(_paths.at(i));
		_messageManager->snapshot("grid-node-" + std::to_string(_me.id) + "-" + std::to_string(i), _draftGrid);
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

void AI::calculateNodes()
{
	Node* node = nullptr;
	_draftGrid.fill(0);

	int group = 1;

	for (int y = 0; y < _grid.height; y++)
	{
		for (int x = 0; x < _grid.width; x++)
		{
			node = new Node(x, y);
			if (calculateNodes(node, group) > 0)
			{
				_rootNodes.push_back(node);
				group++;
			}
			else
			{
				delete node;
				node = nullptr;
			}
		}
	}
	_gridRegions = _draftGrid;
}

int AI::calculateNodes(Node* node, int group)
{
	int nodeCount = 0;
	int x = node->x;
	int y = node->y;

	if (_gridAccess[y][x] > 0)
	{
		if (_draftGrid[y][x] == 0)
		{
			_draftGrid[y][x] = group;
			_nodeList.push_back(node);
			nodeCount++;

			if (y > 0)
			{
				// Left box.
				Node* child = new Node(x, y - 1);
				int count = calculateNodes(child, group);
				if (count > 0)
				{
					node->nodes.push_back(child);
					nodeCount += count;
				}
			}
			if (x > 0)
			{
				// Right box.
				Node* child = new Node(x - 1, y);
				int count = calculateNodes(child, group);
				if (count > 0)
				{
					node->nodes.push_back(child);
					nodeCount += count;
				}
			}
			if (y < _draftGrid.height - 1)
			{
				// Top box.
				Node* child = new Node(x, y + 1);
				int count = calculateNodes(child, group);
				if (count > 0)
				{
					node->nodes.push_back(child);
					nodeCount += count;
				}
			}
			if (x < _draftGrid.width - 1)
			{
				// Top box.
				Node* child = new Node(x + 1, y);
				int count = calculateNodes(child, group);
				if (count > 0)
				{
					node->nodes.push_back(child);
					nodeCount += count;
				}
			}
		}
		else
		{
			nodeCount++;
		}
	}
	return nodeCount;
}

void AI::calculatePaths()
{
	for (size_t n = 0; n < 1; n++) // TODO
	//for (size_t n = 0; n < _nodes.size(); n++)
	{
		Path path;
		calculatePaths(path, _rootNodes.at(n));
	}
}

bool AI::calculatePaths(Path& path, const Node* node)
{
	const Point& p = node->toPoint();

	if (!path.contains(p))
	{
		path.addPoint(p);
		_messageManager->debug("Add point: " + p.toString() + "----" + path.toString());

		bool end = node->nodes.empty();
		for (size_t n = 0; n < node->nodes.size(); n++)
		{
			//end &= !
			calculatePaths(Path(path), node->nodes.at(n));
		}
		//if (end)
		//{
		//	// Store the path unless there are atleast one path possible.
		//	_messageManager->debug("Store path: " + path.toString());
		//	_paths.push_back(path);
		//}

		return true;
	}
	else
	{
		_messageManager->debug("Removed: " + p.toString() + "----" + path.toString());
	}
	return false;
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

void AI::debugNodes()
{

}
