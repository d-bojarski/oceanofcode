#pragma once

#include "messagemanager.h"
#include "player.h"
#include "grid.h"
#include "node.h"
#include "path.h"

#ifdef LIBRARY
#include <qmutex.h>
#endif

class AI
{
public:
	AI(MessageManager* _messageManager);
	~AI();

	void start();
	void stop();


	void calculateGridAccess();
	void calculateNodes();
	int calculateNodes(Node* parentNode, int group);
	void calculatePaths();
	bool calculatePaths(Path& path, const Node* node);


	void calculateUnreachablePath();
	void calculateOptimalPath();

	void debugNodes();

private:
	MessageManager* _messageManager;
	bool _stop;

	Player _me;
	Player _opponent;

	// Grid used for calculation.
	Grid _draftGrid;

	// Grid with sea=0 and earth=1.
	Grid _grid;

	// Grid with access number.
	Grid _gridAccess;

	// Grid with all regions (a number by region).
	Grid _gridRegions;

	// Vector with all nodes.
	std::vector<Node*> _nodeList;
	// Vector with all root nodes (linked).
	std::vector<Node*> _rootNodes;

	// Vector with all paths.
	std::vector<Path> _paths;



	// Grid with unreachable path.
	Grid _gridUnreachablePath;

	// Grid with path already used.
	Grid _gridUsedPath;


#ifdef LIBRARY
	QMutex _mutex;
#endif

};

