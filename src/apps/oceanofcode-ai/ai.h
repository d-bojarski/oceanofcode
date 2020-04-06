#pragma once

#include "messagemanager.h"
#include "player.h"
#include "grid.h"

class AI
{
public:
	AI(const MessageManager& messageManager);
	~AI();

	void start();

	// Fill ground position.
	void fill(short* line, const std::string& lineValue);
	void calculateGridAccess();

	void calculateOptimalPath();

private:
	MessageManager messageManager;
	Player me;
	Player opponent;

	// Grid with sea=0 and earth=1.
	Grid grid;

	// Grid with access number.
	Grid gridAccess;

	// Grid with path already used
	Grid gridUsedPath;
};

