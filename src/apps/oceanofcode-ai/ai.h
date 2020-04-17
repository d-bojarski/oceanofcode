#pragma once

#include "messagemanager.h"
#include "player.h"
#include "grid.h"

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
	void calculatePaths();
	int calculatePaths(Grid& grid, int group, int x, int y);
	void calculateUnreachablePath();
	void calculateOptimalPath();

private:
	MessageManager* _messageManager;
	bool _stop;

	Player _me;
	Player _opponent;

	// Grid with sea=0 and earth=1.
	Grid _grid;

	// Grid with access number.
	Grid _gridAccess;
	
	// Grid with all paths.
	std::vector<Grid> _gridPaths;

	// Grid with unreachable path.
	Grid _gridUnreachablePath;

	// Grid with path already used.
	Grid _gridUsedPath;


#ifdef LIBRARY
	QMutex _mutex;
#endif

};

